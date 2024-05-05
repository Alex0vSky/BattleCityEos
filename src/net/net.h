#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "iappstate.h"
#include "appconfig.h"
#include "game.h"

namespace net {

class NetPlayer : public Player {
	using Player::Player;

public:
	void update(Uint32 dt) override {
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
};

class NetGame : public ::Game {
	void update(Uint32 dt) override;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_player;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count) :
		// tmp
		Game( 1 )
	{}
};
} // namespace net
