// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net.h"
#include "net/tx/DataExchanger.h"
#include "net/tx/EventExchanger.h"
#include "cista/typeHash.h"
#include "cista/xerialize.h"
#include "../ThirdParty/Hexdump.hpp"

#define GETFULLMAP
//#define GETPLAYER
//#ifdef DUMMY
//#endif // DUMMY
namespace net {

auto NetPlayer::cista_members() { return std::tie( 
		*static_cast< Player* >( this ) // reuse serialization from parent
		, m_shots
	); }

void NetPlayer::update(Uint32 dt) {

	const SpriteDataWrapper sprite = m_sprite;
	const int current_frame = m_current_frame;
	// from Tank::update(Uint32 dt)
    const double pos_x_ = Object::pos_x, pos_y_ = Object::pos_y;

	Tank::update( dt );
	m_isDurty = false
			//|| sprite != m_sprite
			//|| current_frame != m_current_frame
			|| pos_x_ != Object::pos_x
			|| pos_y_ != Object::pos_y
		;
	if ( m_isDurty )
		__nop( );

	// Cut keyboard and audio processing
	std::vector< Uint8 > keys;
	{
		int numkeys = 0;
		const Uint8 *key_state = ::SDL_GetKeyboardState( &numkeys );
		keys.resize( numkeys );
		if ( key_state != nullptr ) 
			memcpy( &keys[ 0 ], key_state, numkeys * sizeof( Uint8 ) );
		//SDL_ResetKeyboard( );
	}
	if ( keys.size( ) ) {
		Direction direction_ = Direction::D_INITIAL;
		if ( keys[ player_keys.up ] )
			direction_ = Direction::D_UP;
		else if ( keys[ player_keys.down ] )
			direction_ = Direction::D_DOWN;
		else if ( keys[ player_keys.left ] )
			direction_ = Direction::D_LEFT;
		else if ( keys[ player_keys.right ] )
			direction_ = Direction::D_RIGHT;
		else if ( !testFlag( TankStateFlag::TSF_ON_ICE ) || m_slip_time == 0 )
			speed = 0.0;
		if ( Direction::D_INITIAL != direction_ ) {
			setDirection( direction_ ), speed = default_speed;
			m_isDurty = true;
		}
		// TODO(alex): `Engine::getEngine( ).getAudio( ) ->playSound( ) ...`
		if ( keys[ player_keys.fire ] && m_fire_time > AppConfig::player_reload_time ) {
			NetPlayer::shot( ), m_fire_time = 0;
			//m_isDurty = true;
		}
	}
	m_fire_time += dt;
	if(testFlag(TankStateFlag::TSF_LIFE))
		src_rect = moveRect( m_sprite->rect
			, (
					testFlag(TankStateFlag::TSF_ON_ICE) 
					? static_cast< int >( new_direction ) 
					: static_cast< int >( direction )
				)
			, m_current_frame + 2 * star_count);
	else
		src_rect = moveRect(m_sprite->rect, 0, m_current_frame + 2 * star_count);
	stop = false;
}

void NetPlayer::shot() {
	if ( Bullet* bullet = Player::fire( ) )
		m_shots.insert( m_shots.begin( ), *bullet );
}
NetPlayer::shoots_t NetPlayer::getShots() {
	return std::move( m_shots );
}

bool NetPlayer::getBulletOfShot(Bullet *bullet) {
	return m_shots.empty( ) ? false : ( *bullet = m_shots.back( ), m_shots.pop_back( ), true );
}

template<typename T1, typename T2>
void assignment(T1& lhs, T2 const& rhs) {
	lhs.reserve( rhs.size( ) );
	std::transform(
		rhs.begin( ), rhs.end( ), std::back_inserter( lhs )
		, [](T2::value_type const& element) { 
				typename T1::value_type row;
				row.reserve( element.size( ) );
				std::copy( element.begin( ), element.end( ), std::back_inserter( row ) );
				return row;
			}
	);
}

NetGame::NetGame(int players_count) :
	Game( 1 )
	, m_txEmmiter{ std::make_unique< tx::DataExchanger >( ) }
	, m_txEventer{ std::make_unique< tx::EventExchanger >( ) }
{
	auto tmp0 = cista::type_hash< net::NetPlayer >( );
	// clear generating level for client, from `void Game::clearLevel()`
	if ( NetworkApplicationType::Client == AppConfig::appType ) {
		for ( auto &row : Game::m_level ) {
			for ( auto &item : row ) {
				if ( item != nullptr ) 
					delete item;
				// to '. = empty field'
				item = nullptr;
			}
		}
	}
 
	using Command = tx::DataExchanger::Command;
#ifdef GETFULLMAP
	m_txEmmiter ->setCommandHandler< Command::GetFullMap >( 
			[this](tx::Buffer const& data) mutable ->void
			{
				Level level = *deserialize_< Level >( data );
				std::copy( level.begin( ), level.end( ), NetGame::m_level.begin( ) );
				forEachParentLevel_( [this](int i, int j, Object *&object) {
						if ( nullptr == object )
							__nop( );
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( auto* pval = std::get_if< Object >( &ref ) )
							object = pval;
						if ( auto* pval = std::get_if< Brick >( &ref ) )
							object = pval;
					} );
				//std::vector< std::vector< element_t > > level1_;
				//assignment( level1_, NetGame::m_level ); // tmp check
				//__nop( );
			}
			, [this](void) mutable ->tx::Buffer 
			{
				if ( m_fullMap ) 
					return { };
				m_fullMap = true;
				// for `Game::m_level`
				forEachParentLevel_( [this](int i, int j, Object *&object) {
						if ( nullptr == object )
							return;
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( Brick* brick = dynamic_cast< Brick* >( object ) ) 
							ref = *brick;
						else 
							ref = *object;
					} );
				////std::vector< std::vector< element_t > > level_;
				////assignment( level_, NetGame::m_level ); // tmp check
				////__nop( );

				//if ( !m_playerPtr ->m_isDurty )
				//	co_return;
				//m_playerPtr ->m_isDurty = false;

				////printf( "[server] ptr: %p\n", m_playerPtr ); //
				//printf( "[server] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
				////printf( "[server] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
				//printf( "[server] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //

				//// trace
				//auto trace = ( std::stringstream( )<< Hexdump( data.data( ), std::min( size_t{ 16 }, data.size( ) ) ) ).str( );
				//printf( "[m_txEmmiter::serverSide] %s", trace.c_str( ) );

				return serialize_( NetGame::m_level );
			}
		);
#endif // GETFULLMAP

#ifdef GETPLAYER
	m_txEmmiter ->setCommandHandler< Command::Player >( 
			[this](tx::Buffer const& data) mutable ->void
			{
				//// trace
				//auto trace = ( std::stringstream( )<< Hexdump( data.data( ), std::min( size_t{ 16 }, data.size( ) ) ) ).str( );
				//printf( "[m_txEmmiter::clientSide] %s", trace.c_str( ) );

				//auto buffer1 = data;
				//if ( !deserialize_< NetPlayer >( buffer1 ) ->m_shots.empty( ) )
				//	__nop( );
				//auto playerTmp = *deserialize_< NetPlayer >( data );
				//*m_playerPtr = playerTmp;

				NetPlayer netPlayer = *m_playerPtr;
				netPlayer = *deserialize_< NetPlayer >( data );
				*m_playerPtr = netPlayer;
				//printf( "[client] ptr: %p\n", m_playerPtr ); //
				//printf( "[client] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
				//printf( "[client] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
				//printf( "[client] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //
				__nop( );
			}
			, [this](void) mutable ->tx::Buffer 
			{
				if ( !m_playerPtr ->m_isDurty )
					return { };
				m_playerPtr ->m_isDurty = false;

				return serialize_( *m_playerPtr );
			}
		);
#endif // GETPLAYER

	using EventName = tx::EventExchanger::Eventer::EventName;
	using EventData = tx::EventExchanger::Eventer::EventData;
	using EventShotOwner = tx::EventExchanger::EventData::Shot::Owner;
	m_txEventer ->setCommandHandler< EventName::ClientShot >( 
			[this](void) mutable ->tx::Buffer 
			{
				Bullet bullet;
				if ( !m_playerPtr ->getBulletOfShot( &bullet ) ) 
					return { };
				EventData::Shot eventData{ EventShotOwner::Player, bullet };
				return serialize_( eventData );
			}
			, [this](tx::Buffer const& data) mutable ->void
			{
				auto shot = *deserialize_< EventData::Shot >( data );
				Bullet bullet = shot.bullet;
				printf( "[server] bullet, pos_x/pos_y: %f/%f\n", bullet.pos_x, bullet.pos_y ); //
				// ...
				return;
			}
		);
	m_txEventer ->setCommandHandler< EventName::ClientMovement >( 
			[this](void) mutable ->tx::Buffer 
			{
				if ( !m_playerPtr ->m_isDurty ) 
					return { };
				m_playerPtr ->m_isDurty = false;
				EventData::Movement eventData{ m_playerPtr ->pos_x, m_playerPtr ->pos_y, m_playerPtr ->direction, m_playerPtr ->stop };
				return serialize_( eventData );
			}
			, [this](tx::Buffer const& data) mutable ->void
			{
				auto movement = *deserialize_< EventData::Movement >( data );
				printf( "[server] movement, pos_x/pos_y: %f/%f\n", movement.pos_x, movement.pos_y ); //
				m_playerPtr ->pos_x = movement.pos_x;
				m_playerPtr ->pos_y = movement.pos_y;
				//m_playerPtr ->stop = movement.stop;
				m_playerPtr ->setDirection( movement.direction );
				return;
			}
		);
}
NetGame::~NetGame()
{
	//Game::m_players.clear( );
	//m_playerPtr.reset( );
	forEachParentLevel_( [this](int i, int j, Object *&object) {
			if ( nullptr == object )
				return;
			delete object;
			object = nullptr;
		} );
	Game::m_level.clear( );
	m_txEmmiter.reset( );
	m_txEventer.reset( );
}

void NetGame::generateEnemy() {
	// dont generate ememies for client
	if ( NetworkApplicationType::Server == AppConfig::appType )
		Game::generateEnemy( );
}
void NetGame::update(Uint32 dt) {
	// Initial rewrite
	if ( !m_playerPtr ) {
		for ( auto player : Game::m_players ) 
			delete player;
		Game::m_players.clear( );

		unsigned playerIndex = 0;
		m_playerPtr = std::make_shared< NetPlayer > ( 
				AppConfig::player_starting_point.at( playerIndex ).x
				, AppConfig::player_starting_point.at( playerIndex ).y
				, sprite_t::ST_PLAYER_1
			);
		m_playerPtr ->player_keys = AppConfig::player_keys.at( playerIndex );
		++playerIndex;
		Game::m_players.push_back( m_playerPtr.get( ) );

		NetGame::m_level.resize( Game::m_level.size( ) );
		std::for_each( Game::m_level.begin( ), Game::m_level.end( ), [this](std::vector<Object *> &element) {
			    int i = &element - &Game::m_level[ 0 ];
				NetGame::m_level[ i ].resize( element.size( ) );
			} );

		//std::vector< std::vector< element_t > > level_;
		//assignment( level_, NetGame::m_level ); // tmp check
		//__nop( );

		//// tmp
		//m_playerPtr ->setFlag( TankStateFlag::TSF_LIFE );
		//Bullet* bullet = m_playerPtr ->fire( );
		//m_playerPtr ->clearFlag( TankStateFlag::TSF_LIFE );
		//m_playerPtr ->m_shots.push_back( *bullet );
		////auto buffer0 = serialize_( m_playerPtr ->m_shots );
		////auto asd0 = *deserialize_< net::NetPlayer::shoots_t >( buffer0 );
		//auto buffer1 = serialize_( *m_playerPtr );
		//auto asd1 = *deserialize_< net::NetPlayer >( buffer1 );
		__nop( );
	}

	if ( NetworkApplicationType::IntraProcess != AppConfig::appType || !m_playerPtr ->m_isDurty ) {
		Game::update( dt );
		//printf( "[NetGam] m_flags: %d\n", (int)m_playerPtr ->m_flags ); //
		//printf( "[NetGam] m_current_frame: %d\n", (int)m_playerPtr ->m_current_frame ); //
		//printf( "[NetGam] pos_y: %d\n", (int)m_playerPtr ->pos_y ); //
		//m_playerPtr ->m_isDurty = true;
	}

	if ( m_txEmmiter ) m_txEmmiter ->update( ); // Eventer check, commented
	if ( m_txEventer ) m_txEventer ->update( ); // Eventer check, uncommented
}
void NetGame::draw() {
    Engine& engine = Engine::getEngine();
    Renderer* renderer = engine.getRenderer();
    renderer->clear();

    if(m_level_start_screen)
    {
        std::string level_name = "STAGE " + Engine::intToString(m_current_level);
        renderer->drawText(nullptr, level_name, {255, 255, 255, 255}, 1);
    }
    else
    {
        renderer->drawRect(&AppConfig::map_rect, {0, 0, 0, 0}, true);
        for(auto row : Game::m_level)
            for(auto item : row)
                if(item != nullptr) item->draw();

        for(auto player : m_players) player->draw();
		// tmp comment
        for(auto enemy : m_enemies) enemy->draw();
        for(auto bush : m_bushes) bush->draw();
        for(auto bonus : m_bonuses) bonus->draw();
        m_eagle->draw();

        if(m_game_over)
        {
            point_t pos;
            pos.x = -1;
            pos.y = m_game_over_position;
            renderer->drawText(&pos, AppConfig::game_over_text.data( ), {255, 10, 10, 255});
			Engine::getEngine( ).getAudio( ) ->playSound( ) ->gameover( );
        }

        //=============Game Status=============
        rect_t src = engine.getSpriteConfig()->getSpriteData(sprite_t::ST_LEFT_ENEMY)->rect;
        rect_t dst;
        point_t p_dst;
        //enemies to kill
        for(int i = 0; i < static_cast<int>(m_enemy_to_kill); i++)
        {
            dst = {AppConfig::status_rect.x + 8 + src.w * (i % 2), 5 + src.h * (i / 2), src.w, src.h};
            renderer->drawObject(src, dst);
        }
        //player lives
        int i = 0;
        for(auto player : m_players)
        {
            dst = {AppConfig::status_rect.x + 5, i * 18 + 180, 16, 16};
            p_dst = {dst.x + dst.w + 2, dst.y + 3};
            i++;
            renderer ->drawObject( player->src_rect, dst );
            renderer->drawText(&p_dst, Engine::intToString(player->lives_count), {0, 0, 0, 255}, 3);
        }
        //map number
        src = engine.getSpriteConfig()->getSpriteData(sprite_t::ST_STAGE_STATUS)->rect;
        dst = {AppConfig::status_rect.x + 8, static_cast<int>(185 + (m_players.size() + m_killed_players.size()) * 18), src.w, src.h};
        p_dst = {dst.x + 10, dst.y + 26};
        renderer->drawObject(src, dst);
        renderer->drawText(&p_dst, Engine::intToString(m_current_level), {0, 0, 0, 255}, 2);

        if(m_pause)
            renderer->drawText(nullptr, std::string("PAUSE"), {200, 0, 0, 255}, 1);
    }

    renderer->flush();
}
} // namespace net
