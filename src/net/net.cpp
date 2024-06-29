// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net.h"
#include "..\ThirdParty\Hexdump.hpp"
namespace net {
void NetPlayer::update(Uint32 dt) {
	Tank::update( dt );
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
		m_movement = false;
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
		if ( Direction::D_INITIAL != direction_ )
			setDirection( direction_ ), speed = default_speed, m_movement = true;
		// TODO(alex): `Engine::getEngine( ).getAudio( ) ->playSound( ) ...`

		if ( keys[ player_keys.fire ] && m_fire_time > AppConfig::player_reload_time )
			NetPlayer::shoot( ), m_fire_time = 0;
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

void NetPlayer::shoot()
{
	////Bullet* b = Tank::fire();
	////if(b != nullptr)
	////{
	////    if(star_count > 0) b->speed = AppConfig::bullet_default_speed * 1.3;
	////    if(star_count == 3) b->increased_damage = true;
	////}
	////return b;
	if ( Bullet* bullet = Player::fire( ) )
	//	m_shoots.push( *bullet );
	__nop( );
}
//NetPlayer::shoots_t NetPlayer::getShoots() {
//	return std::move( m_shoots );
//}

template<typename T1, typename T2>
void assignment(T1& lhs, T2 const& rhs) {
	lhs.reserve( rhs.size( ) );
	std::transform(
		rhs.begin( ), rhs.end( ), std::back_inserter( lhs )
		, [](T2::value_type const& element) { 
				T1::value_type row;
				row.reserve( element.size( ) );
				std::copy( element.begin( ), element.end( ), std::back_inserter( row ) );
				return row;
			}
	);
}

NetGame::NetGame(int players_count, bool isServer) :
	Game( 1 )
	, m_isServer( isServer )
	, m_txEmmiter( isServer ), m_txEventer( isServer ) // comment it if intraProcess
{
	auto tmp0 = cista::type_hash< net::NetPlayer >( );
	m_txEmmiter.setUpdateCallbacks( 
			[this](tx::DataExchanger *tx) mutable ->tx::DataExchanger::awaitable {
				cista::byte_buf buffer;
				//if ( co_await tx ->clientSide( tx::DataExchanger::Command::GetFullMap, &buffer ) ) {
				//	level_t level = *deserialize_< level_t >( buffer );
				//	std::copy( level.begin( ), level.end( ), NetGame::m_level.begin( ) );
				//	forEachLevel_( [this](int i, int j, Object *&object) {
				//			auto &ref = NetGame::m_level[ i ][ j ];
				//			if ( auto* pval = std::get_if< Object >( &ref ) )
				//				*object = *pval;
				//			if ( auto* pval = std::get_if< Brick >( &ref ) )
				//				*object = *pval;
				//		} );
				//	std::vector< std::vector< element_t > > level1_;
				//	assignment( level1_, NetGame::m_level ); // tmp check
				//	__nop( );
				//}
				if ( co_await tx ->clientSide( tx::DataExchanger::Command::Something, &buffer ) ) {
					//// trace
					//auto trace = ( std::stringstream( )<< Hexdump( buffer.data( ), std::min( size_t{ 16 }, buffer.size( ) ) ) ).str( );
					//printf( "[m_txEmmiter::clientSide] %s", trace.c_str( ) );

					*m_playerPtr = *deserialize_< NetPlayer >( buffer );
					__nop( );
				}
				__nop( );
			}
			, [this](tx::DataExchanger *tx) mutable ->tx::DataExchanger::awaitable {
				__nop( );
				forEachLevel_( [this](int i, int j, Object *&object) {
						auto &ref = NetGame::m_level[ i ][ j ];
						if ( Brick* brick = dynamic_cast< Brick* >( object ) ) 
							ref = *brick;
						else 
							ref = *object;
					} );
				//std::vector< std::vector< element_t > > level_;
				//assignment( level_, NetGame::m_level ); // tmp check
				//__nop( );

				auto buffer = serialize_( *m_playerPtr ); // tmp
				//// trace
				//auto trace = ( std::stringstream( )<< Hexdump( buffer.data( ), std::min( size_t{ 16 }, buffer.size( ) ) ) ).str( );
				//printf( "[m_txEmmiter::serverSide] %s", trace.c_str( ) );

				co_await tx ->serverSide( )
						//->on( tx::DataExchanger::Command::GetFullMap, serialize_( NetGame::m_level ) )
						//->on( tx::DataExchanger::Command::Something, serialize_( *m_playerPtr ) )
						->on( tx::DataExchanger::Command::Something, buffer ) // tmp
						->finish( )
					;
				__nop( );
			}
		);
	m_txEventer.setUpdateCallbacks(
			[this](tx::EventExchanger *tx) mutable ->tx::EventExchanger::awaitable { co_return; }
			, [this](tx::EventExchanger *tx) mutable ->tx::EventExchanger::awaitable { co_return; }
		);

	/*
	m_txEventer.setUpdateCallbacks(
			// TODO(alex): where are send data from client?
			[this](tx::EventExchanger *tx) mutable ->tx::EventExchanger::awaitable {
				NetPlayer::shoots_t shoots = m_playerPtr ->getShoots( );
				while ( !shoots.empty( ) ) {
					EventData::Shoot eventData{ EventShootOwner::Player, shoots.front( ) };
					shoots.pop( );
					co_await tx ->clientSideEvent( EventName::ClientShoot, serialize_( eventData ) );
					////	TODO(alex): or
					//co_await tx ->clientSideEvent( Tx::Command::EventClientShoot, bufferOut );
					//co_await tx ->clientSide( ) ->Event( Tx::EventClient::Shoot, unit_t );
					//co_await tx ->clientSide( ).Event( Tx::EventClient::Shoot, unit_t );
					////	TODO(alex): or `[this](TxClientSide *tx) mutable ->Tx::awaitable {`
					// TODO(alex): renameme clientSide = clientSideData/clientGetEmitted/getEmitted/getEmittedData
					// TODO(alex): renameme Tx::Command = Tx::Emmit
					// TODO(alex): makeme Tx::EventClient
				}
				co_return;
			}
			, [this](tx::EventExchanger *tx) mutable ->tx::EventExchanger::awaitable {
				co_await tx ->serverSideEvent( )
						// a callbacks because of passive or because of server
						->onShoot( EventName::ClientShoot, [this] (EventData::Shoot const& eventData) {
								if ( EventShootOwner::Player == eventData.owner ) {
									// TODO(alex): makeme
									//addToUpdate( shoot.bullet );
								}
								__nop( );
							} )
						->finish( )
					;
			}
		);
	//*/
}
NetGame::~NetGame()
{
	//Game::m_players.clear( );
	//m_playerPtr.reset( );
}

void NetGame::update(Uint32 dt) {
	if ( m_playerPtr ) {
		//NetPlayer *player;
		//cista::byte_buf buffer = serialize( *m_playerPtr );
		//player = deserialize< c_MODE >( buffer );
		//*m_playerPtr = *player;

		m_txEmmiter.update( );
		//m_txEventer.update( );
	}
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
	}

	Game::update( dt );
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
        //for(auto enemy : m_enemies) enemy->draw();
        //for(auto bush : m_bushes) bush->draw();
        //for(auto bonus : m_bonuses) bonus->draw();
        //m_eagle->draw();

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

using hash_t = cista::hash_t;

hash_t type_hash(net::NetGame::element_t const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetGame::element_t" ) );
}

// Empty
template <typename Ctx>
void serialize(Ctx & context, net::NetGame::element_t const* el, cista::offset_t const offset) {}

hash_t type_hash(SpriteDataWrapper const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}

template <typename Ctx>
void serialize(Ctx & context, SpriteDataWrapper const* el, cista::offset_t const offset) {
	using cista::serialize;
	//serialize( context, &el ->m_sprite, offset + offsetof( SpriteDataWrapper, m_sprite ) );
	context.write( offset + offsetof( SpriteDataWrapper, m_sprite ), nullptr );
	serialize( context, &el ->m_spriteType, offset + offsetof( SpriteDataWrapper, m_spriteType ) );
}

template <typename Ctx>
void deserialize(Ctx const& c, net::NetGame::level_t* el) {
	const auto &sc = Engine::getEngine( ).getSpriteConfig( );
	for ( auto &row : *el )
		for ( auto &col: row ) {
			if ( auto* pval = std::get_if< Object >( &col ) ) {
				deserialize( c, pval );
			}
			if ( auto* pval = std::get_if< Brick >( &col ) ) {
				deserialize( c, pval );
			}
			__nop( );
		}
}

template <typename Ctx>
void deserialize(Ctx const& c, SpriteDataWrapper* el) {
	const auto &sc = Engine::getEngine( ).getSpriteConfig( );
	const SpriteData* spriteData = nullptr;
	const sprite_t spriteType = el ->getType( );
	if ( sprite_t::ST_NONE != spriteType )
		spriteData = sc ->getSpriteData( spriteType );
	*el = spriteData;
}

template <typename Ctx>
void deserialize(Ctx const& c, net::NetPlayer* el) {
	const auto &sc = Engine::getEngine().getSpriteConfig();
	sprite_t spriteType;
	el ->m_sprite = sc ->getSpriteData( el ->m_sprite.getType( ) );
	spriteType = el ->m_shield.m_sprite.getType( );
	const SpriteData* spriteData = nullptr;
	if ( sprite_t::ST_NONE != spriteType )
		spriteData = sc ->getSpriteData( spriteType );
	el ->m_shield.m_sprite = spriteData;

	for ( auto &bullet : el ->bullets )
		bullet.m_sprite = sc ->getSpriteData( bullet.m_sprite.getType( ) );
}
