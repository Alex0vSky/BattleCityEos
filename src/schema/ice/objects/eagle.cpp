// src\schema\ice\objects\eagle.cpp // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "eagle.h"
#include "engine/engine.h"

Eagle::Eagle()
    : BaseObject(0, 0, sprite_t::ST_EAGLE)
{
}

Eagle::Eagle(double x, double y)
    : BaseObject(x, y, sprite_t::ST_EAGLE)
{
}

void Eagle::update(Uint32 dt)
{
    if(type == sprite_t::ST_DESTROY_EAGLE)
    {
        m_frame_display_time += dt;
        if(m_frame_display_time > m_sprite->frame_duration)
        {
            m_frame_display_time = 0;
            m_current_frame++;
            if(m_current_frame >= m_sprite->frames_count)
            {
                m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(sprite_t::ST_FLAG);
                m_current_frame = 0;
                type = sprite_t::ST_FLAG;
                update(0);
            }
            src_rect = moveRect(m_sprite->rect, 0, m_current_frame);
        }
    }
    else
        BaseObject::update(dt);
}

void Eagle::destroy()
{
    if(type != sprite_t::ST_EAGLE) return;

    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(sprite_t::ST_DESTROY_EAGLE);
    type = sprite_t::ST_DESTROY_EAGLE;
    src_rect = moveRect(m_sprite->rect, 0, 0);

    dest_rect.x = pos_x + (dest_rect.w - m_sprite->rect.w)/2;
    dest_rect.y = pos_y + (dest_rect.h - m_sprite->rect.h)/2;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;
}
