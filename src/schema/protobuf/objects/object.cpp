// src\schema\protobuf\objects\object.cpp // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "engine/engine.h"

Object::Object(double x, double y, sprite_t type)
{
    pos_x = ( x );
    pos_y = ( y );
    this->type = type;
    to_erase = false;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(type);
	frame_display_time = ( 0 );
	current_frame = ( 0 );

    src_rect.x = m_sprite->rect.x;
    src_rect.y = m_sprite->rect.y;
    src_rect.h = m_sprite->rect.h;
    src_rect.w = m_sprite->rect.w;

    dest_rect.x = pos_x;
    dest_rect.y = pos_y;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = pos_x;
    collision_rect.y = pos_y;
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;
}

Object::Object(double x, double y, const SpriteData *sprite)
{
    pos_x = ( x );
    pos_y = ( y );
    to_erase = false;
    m_sprite = sprite;
	frame_display_time = ( 0 );
	current_frame = ( 0 );

    src_rect.x = m_sprite->rect.x;
    src_rect.y = m_sprite->rect.y;
    src_rect.h = m_sprite->rect.h;
    src_rect.w = m_sprite->rect.w;

    dest_rect.x = pos_x;
    dest_rect.y = pos_y;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = pos_x;
    collision_rect.y = pos_y;
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;
}

Object::~Object()
{
}

void Object::draw()
{
    if(m_sprite == nullptr || to_erase) return;
    Engine::getEngine( ).getRenderer( ) ->drawObject( src_rect, dest_rect );
}

void Object::update(Uint32 dt)
{
    if(to_erase) return;

    dest_rect.x = pos_x;
    dest_rect.y = pos_y;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = pos_x;
    collision_rect.y = pos_y;
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;

    if(m_sprite->frames_count > 1)
    {
		frame_display_time = ( frame_display_time + dt );
		if ( frame_display_time > m_sprite ->frame_duration )
        {
			frame_display_time = ( 0 );
			current_frame = ( current_frame + 1 );
			if ( current_frame >= m_sprite ->frames_count )
            {
                if ( m_sprite ->loop ) current_frame = ( 0 );
                else current_frame = ( m_sprite->frames_count - 1 );
            }

			src_rect = moveRect( m_sprite ->rect, 0, current_frame );
        }
    }
}

SDL_Rect Object::moveRect(const SDL_Rect &rect, int x, int y)
{
    SDL_Rect r;
    r.x = rect.x + x*rect.w;
    r.y = rect.y + y*rect.h;
    r.w = rect.w;
    r.h = rect.h;

    return r;
}
SDL_Rect Object::moveRect(const SDL_Rect &rect, Direction x, int y)
{
	return moveRect( rect, static_cast<int>( x ), y );
}

SDL_Rect intersectRect(SDL_Rect const& rect1, SDL_Rect const& rect2)
{
    SDL_Rect intersect_rect;
    intersect_rect.x = std::max(rect1.x, rect2.x);
    intersect_rect.y = std::max(rect1.y, rect2.y);
    intersect_rect.w = std::min(rect1.x + rect1.w, rect2.x + rect2.w) - intersect_rect.x;
    intersect_rect.h = std::min(rect1.y + rect1.h, rect2.y + rect2.h) - intersect_rect.y;

    return intersect_rect;
}
