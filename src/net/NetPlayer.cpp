// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "NetPlayer.h"

namespace net {

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
} // namespace net
