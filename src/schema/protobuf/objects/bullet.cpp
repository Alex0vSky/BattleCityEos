// src\schema\protobuf\objects\bullet.cpp // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "bullet.h"
#include "appconfig.h"

Bullet::Bullet(double x, double y)
    : Object(x, y, sprite_t::ST_BULLET)
{
	Object::addToReplicationGraph( m_dataOffline );
    speed = 0.0;
    direction = Direction::D_UP;
    increased_damage = false;
    collide = false;
}

void Bullet::update(Uint32 dt)
{
    if(!collide)
    {
        switch (direction)
        {
        case Direction::D_UP:
			pos_y = ( pos_y - speed * dt );
            break;
        case Direction::D_RIGHT:
			pos_x = ( pos_x + speed * dt );
            break;
        case Direction::D_DOWN:
			pos_y = ( pos_y + speed * dt );
            break;
        case Direction::D_LEFT:
			pos_x = ( pos_x - speed * dt );
            break;
        }

        src_rect = moveRect(m_sprite->rect, direction, 0);
        Object::update(dt);
    }
    else
    {
        if(m_sprite->frames_count > 1)
        {
			frame_display_time = ( frame_display_time + dt );
			if ( frame_display_time > m_sprite ->frame_duration )
            {
				frame_display_time = ( 0 );
				current_frame = ( current_frame + 1 );
				if ( current_frame >= m_sprite ->frames_count )
					to_erase = ( true );

				src_rect = moveRect( m_sprite->rect, 0, current_frame );
            }
        }
    }
}

void Bullet::destroy()
{
    if(collide) return; //prevents multiple calls

    collide = true;
    speed = 0;
    current_frame = ( 0 );
    frame_display_time = ( 0 );
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(sprite_t::ST_DESTROY_BULLET);

    switch(direction)
    {
    case Direction::D_UP:
        dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w) / 2; // dest_rect.w, dest_rect.h - old bullet size
        dest_rect.y = pos_y - m_sprite->rect.h / 2;
        break;
    case Direction::D_RIGHT:
        dest_rect.x = pos_x + dest_rect.w - m_sprite->rect.w / 2;
        dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h) / 2;
        break;
    case Direction::D_DOWN:
        dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w) / 2;
        dest_rect.y = pos_y + dest_rect.h - m_sprite->rect.h / 2;
        break;
    case Direction::D_LEFT:
        dest_rect.x = pos_x - m_sprite->rect.w / 2;
        dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h) / 2;
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
