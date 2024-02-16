// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "bullet.h"
#include "appconfig.h"

Bullet::Bullet()
    : Object(0, 0, ST_BULLET)
{
    speed = 0.0;
    direction = D_UP;
    increased_damage = false;
    collide = false;
}

Bullet::Bullet(double x, double y)
    : Object(x, y, ST_BULLET)
{
    speed = 0.0;
    direction = D_UP;
    increased_damage = false;
    collide = false;
}

void Bullet::update(Uint32 dt)
{
    if(!collide)
    {
        switch (direction)
        {
        case D_UP:
			dataReplicable( ).set_pos_y( dataReplicable( ).pos_y( ) - speed * dt );
            break;
        case D_RIGHT:
			dataReplicable( ).set_pos_x( dataReplicable( ).pos_x( ) + speed * dt );
            break;
        case D_DOWN:
			dataReplicable( ).set_pos_y( dataReplicable( ).pos_y( ) + speed * dt );
            break;
        case D_LEFT:
			dataReplicable( ).set_pos_x( dataReplicable( ).pos_x( ) - speed * dt );
            break;
        }

        src_rect = moveRect(m_sprite->rect, direction, 0);
        Object::update(dt);
    }
    else
    {
        if(m_sprite->frames_count > 1)
        {
			dataOffline( ).set_frame_display_time( dataOffline( ).frame_display_time( ) + dt );
			if ( dataOffline( ).frame_display_time( ) > m_sprite ->frame_duration )
            {
				dataOffline( ).set_frame_display_time( 0 );
				dataOffline( ).set_current_frame( dataOffline( ).current_frame( ) + 1 );
				if ( dataOffline( ).current_frame( ) >= m_sprite ->frames_count )
                    to_erase = true;

				src_rect = moveRect( m_sprite->rect, 0, dataOffline( ).current_frame( ) );
            }
        }
    }
}

void Bullet::destroy()
{
    if(collide) return; //prevents multiple calls

    collide = true;
    speed = 0;
    dataOffline( ).set_current_frame( 0 );
    dataOffline( ).set_frame_display_time( 0 );
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_DESTROY_BULLET);

    switch(direction)
    {
    case D_UP:
        dest_rect.x = dataReplicable( ).pos_x( ) + (dest_rect.w - m_sprite->rect.w) / 2; // dest_rect.w, dest_rect.h - old bullet size
        dest_rect.y = dataReplicable( ).pos_y( ) - m_sprite->rect.h / 2;
        break;
    case D_RIGHT:
        dest_rect.x = dataReplicable( ).pos_x( ) + dest_rect.w - m_sprite->rect.w / 2;
        dest_rect.y = dataReplicable( ).pos_y( ) + (dest_rect.h - m_sprite->rect.h) / 2;
        break;
    case D_DOWN:
        dest_rect.x = dataReplicable( ).pos_x( ) + (dest_rect.w - m_sprite->rect.w) / 2;
        dest_rect.y = dataReplicable( ).pos_y( ) + dest_rect.h - m_sprite->rect.h / 2;
        break;
    case D_LEFT:
        dest_rect.x = dataReplicable( ).pos_x( ) - m_sprite->rect.w / 2;
        dest_rect.y = dataReplicable( ).pos_y( ) + (dest_rect.h - m_sprite->rect.h) / 2;
        break;
    }

    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    src_rect.x = m_sprite->rect.x;
    src_rect.y = m_sprite->rect.y;
    src_rect.h = m_sprite->rect.h;
    src_rect.w = m_sprite->rect.w;

	// TODO(alex): multiple explosion types
	Engine::getEngine( ).getAudio( ) ->playSound( ) ->explosion( );
}
