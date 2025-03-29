// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/NetGame.h"
#include "net/NetPlayer.h"
#include "xerialization.h"
//#include "../ThirdParty/Hexdump.hpp"

namespace net {
void NetGame::eventer_()
{ 
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
				EventData::Shot shot;
				deserialize_( data, &shot );
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
				EventData::Movement movement;
				deserialize_( data, &movement );
				printf( "[server] movement, pos_x/pos_y: %f/%f\n", movement.pos_x, movement.pos_y ); //
				m_playerPtr ->pos_x = movement.pos_x;
				m_playerPtr ->pos_y = movement.pos_y;
				//m_playerPtr ->stop = movement.stop;
				m_playerPtr ->setDirection( movement.direction );
				return;
			}
		);
}
} // namespace net
    