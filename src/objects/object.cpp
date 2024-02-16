// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "engine/engine.h"

Object::Object()
{
    dataReplicable( ).set_pos_x( 0.0 );
    dataReplicable( ).set_pos_y( 0.0 );
    type = ST_NONE;
    to_erase = false;
    m_sprite = nullptr;
	dataOffline( ).set_frame_display_time( 0 );
	dataOffline( ).set_current_frame( 0 );
}

Object::Object(double x, double y, SpriteType type)
{
    dataReplicable( ).set_pos_x( x );
    dataReplicable( ).set_pos_y( y );
    this->type = type;
    to_erase = false;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(type);
	dataOffline( ).set_frame_display_time( 0 );
	dataOffline( ).set_current_frame( 0 );

    src_rect.x = m_sprite->rect.x;
    src_rect.y = m_sprite->rect.y;
    src_rect.h = m_sprite->rect.h;
    src_rect.w = m_sprite->rect.w;

    dest_rect.x = dataReplicable( ).pos_x( );
    dest_rect.y = dataReplicable( ).pos_y( );
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = dataReplicable( ).pos_x( );
    collision_rect.y = dataReplicable( ).pos_y( );
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;
}

Object::Object(double x, double y, const SpriteData *sprite)
{
    dataReplicable( ).set_pos_x( x );
    dataReplicable( ).set_pos_y( y );
    this->type = type;
    to_erase = false;
    m_sprite = sprite;
	dataOffline( ).set_frame_display_time( 0 );
	dataOffline( ).set_current_frame( 0 );

    src_rect.x = m_sprite->rect.x;
    src_rect.y = m_sprite->rect.y;
    src_rect.h = m_sprite->rect.h;
    src_rect.w = m_sprite->rect.w;

    dest_rect.x = dataReplicable( ).pos_x( );
    dest_rect.y = dataReplicable( ).pos_y( );
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = dataReplicable( ).pos_x( );
    collision_rect.y = dataReplicable( ).pos_y( );
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;
}

Object::~Object()
{
}

void Object::draw()
{
    if(m_sprite == nullptr || to_erase) return;
    Engine::getEngine().getRenderer()->drawObject(&src_rect, &dest_rect);
}

void Object::update(Uint32 dt)
{
    if(to_erase) return;

    dest_rect.x = dataReplicable( ).pos_x( );
    dest_rect.y = dataReplicable( ).pos_y( );
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;

    collision_rect.x = dataReplicable( ).pos_x( );
    collision_rect.y = dataReplicable( ).pos_y( );
    collision_rect.h = m_sprite->rect.h;
    collision_rect.w = m_sprite->rect.w;

    if(m_sprite->frames_count > 1)
    {
		dataOffline( ).set_frame_display_time( dataOffline( ).frame_display_time( ) + dt );
		if ( dataOffline( ).frame_display_time( ) > m_sprite ->frame_duration )
        {
			dataOffline( ).set_frame_display_time( 0 );
			dataOffline( ).set_current_frame( dataOffline( ).current_frame( ) + 1 );
			if ( dataOffline( ).current_frame( ) >= m_sprite ->frames_count )
            {
                if ( m_sprite ->loop ) dataOffline( ).set_current_frame( 0 );
                else dataOffline( ).set_current_frame( m_sprite->frames_count - 1 );
            }

			src_rect = moveRect( m_sprite ->rect, 0, dataOffline( ).current_frame( ) );
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


SDL_Rect intersectRect(SDL_Rect *rect1, SDL_Rect *rect2)
{
    SDL_Rect intersect_rect;
    intersect_rect.x = std::max(rect1->x, rect2->x);
    intersect_rect.y = std::max(rect1->y, rect2->y);
    intersect_rect.w = std::min(rect1->x + rect1->w, rect2->x + rect2->w) - intersect_rect.x;
    intersect_rect.h = std::min(rect1->y + rect1->h, rect2->y + rect2->h) - intersect_rect.y;

    return intersect_rect;
}
