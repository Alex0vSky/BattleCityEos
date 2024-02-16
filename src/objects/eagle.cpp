// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "eagle.h"
#include "engine/engine.h"

Eagle::Eagle()
    : Object(0, 0, ST_EAGLE)
{
}

Eagle::Eagle(double x, double y)
    : Object(x, y, ST_EAGLE)
{
}

void Eagle::update(Uint32 dt)
{
    if(type == ST_DESTROY_EAGLE)
    {
		dataOffline( ).set_frame_display_time( dataOffline( ).frame_display_time( ) + dt );
		if ( dataOffline( ).frame_display_time( ) > m_sprite ->frame_duration )
        {
			dataOffline( ).set_frame_display_time( 0 );
			dataOffline( ).set_current_frame( dataOffline( ).current_frame( ) + 1 );
			if ( dataOffline( ).current_frame( ) >= m_sprite ->frames_count )
            {
                m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_FLAG);
				dataOffline( ).set_current_frame( 0 );
                type = ST_FLAG;
                update(0);
            }
			src_rect = moveRect( m_sprite->rect, 0, dataOffline( ).current_frame( ) );
        }
    }
    else
        Object::update(dt);
}

void Eagle::destroy()
{
    if(type != ST_EAGLE) return;

    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_DESTROY_EAGLE);
    type = ST_DESTROY_EAGLE;
    src_rect = moveRect(m_sprite->rect, 0, 0);

    dest_rect.x = dataReplicable( ).pos_x( ) + (dest_rect.w - m_sprite->rect.w)/2;
    dest_rect.y = dataReplicable( ).pos_y( ) + (dest_rect.h - m_sprite->rect.h)/2;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;
}
