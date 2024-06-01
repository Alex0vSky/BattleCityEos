// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net.h"

#include <boost/config/user.hpp>
#include <boost/asio.hpp>

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
			fire( ), m_fire_time = 0;
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

NetGame::NetGame(int players_count) :
	Game( 1 )
	, m_ioContext( std::make_unique< boost::asio::io_context >( 1 ) )
{}

void NetGame::update(Uint32 dt) {
	if ( m_player ) {
		//NetPlayer *player;
		//cista::byte_buf buffer = cista::serialize< c_MODE >( *m_player );
		//player = cista::deserialize< NetPlayer, c_MODE >( buffer );
		//*m_player = *player;

		// No signals and calling shortcut not working in my msvc: as_tuple_t< use_awaitable_t< > >;
		co_spawn_( [this]() mutable ->awaitable {
				printf( "[serv] acceptor...\n" );
				tcp::acceptor acceptor( *m_ioContext, { tcp::v4( ), c_port } );
				while ( !m_ioContext ->stopped( ) ) {
					auto [error1, socket] = co_await acceptor.async_accept( c_tuple );
					if ( !socket.is_open( ) || error1 ) 
						continue;
					command_t commandRaw; const size_t commandSizeof = sizeof( commandRaw );
					auto [error3, n] = co_await socket.async_read_some( boost::asio::buffer( &commandRaw, commandSizeof ), c_tuple );
					if ( n != commandSizeof || error3 ) 
						continue;
					const auto command = static_cast< Command >( commandRaw );
					if ( Command::Something == command ) { 
						cista::byte_buf buffer = cista::serialize< c_MODE >( *m_player );
						auto [error2, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( buffer ), c_tuple );
						if ( buffer.size( ) != nwritten ) {
							printf( "[serv] write failed: '%s'\n", error2.message( ).c_str( ) );
							continue;
						}
					}
					// TODO(alex): makeme Command::GetFullMap
					//for ( auto row : m_level )
					//	for ( auto item : row )
					//		if ( item != nullptr ) item ...;
					socket.shutdown( boost::asio::socket_base::shutdown_send );
				}
			} );
		
		co_spawn_( [this]() mutable ->awaitable {
				while ( !m_ioContext ->stopped( ) ) {
					tcp::socket socket( co_await boost::asio::this_coro::executor );
					auto [error1] = co_await socket.async_connect( { address_v4( c_host ), c_port }, c_tuple );
					if ( error1 ) {
						printf( "[reader] connect failed: '%s'\n", error1.message( ).c_str( ) );
						continue;
					}

					const auto command = static_cast< command_t >( Command::Something );
					const size_t commandSizeof = sizeof( command );
					auto [error3, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( &command, commandSizeof ), c_tuple );
					if ( nwritten != commandSizeof || error3 ) 
						continue;

					cista::byte_buf buffer;
					while ( true ) {
						std::uint8_t data[ 1024 ];
						auto [error2, n] = co_await socket.async_read_some( boost::asio::buffer( data ), c_tuple );
						if ( n ) 
							std::copy( data, data + n, std::back_inserter( buffer ) );
						if ( boost::asio::error::eof == error2 ) {
							socket.shutdown( boost::asio::socket_base::shutdown_receive );
							*m_player = *cista::deserialize< NetPlayer, c_MODE >( buffer );
							m_ioContext ->stop( );
							break;
						}
						if ( error2 ) {
							printf( "[reader] read failed: '%s'\n", error2.message( ).c_str( ) );
							break;
						}
					}
				}
			} );
		if ( m_ioContext ->stopped( ) ) 
			m_ioContext ->restart( );
		m_ioContext ->run( );
		__nop( );
	}
	// Initial rewrite
	if ( !m_player ) {
		for ( auto player : Game::m_players ) 
			delete player;
		Game::m_players.clear( );

		unsigned playerIndex = 0;
		m_player = std::make_shared< NetPlayer > ( 
				AppConfig::player_starting_point.at( playerIndex ).x
				, AppConfig::player_starting_point.at( playerIndex ).y
				, sprite_t::ST_PLAYER_1
			);
		m_player ->player_keys = AppConfig::player_keys.at( playerIndex );
		++playerIndex;
		Game::m_players.push_back( m_player.get( ) );
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
        //for(auto row : m_level)
        //    for(auto item : row)
        //        if(item != nullptr) item->draw();

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
hash_t type_hash(SpriteDataWrapper const& el, hash_t h,
                 std::map<hash_t, unsigned>& done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}

template <typename Ctx>
inline void serialize(Ctx & context, SpriteDataWrapper const* el, cista::offset_t const offset) {
	using cista::serialize;
	serialize( context, &el ->m_sprite, offset + offsetof( SpriteDataWrapper, m_sprite ) );
	serialize( context, &el ->m_spriteType, offset + offsetof( SpriteDataWrapper, m_spriteType ) );
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
