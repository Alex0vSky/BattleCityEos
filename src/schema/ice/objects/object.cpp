// src\schema\ice\objects\object.cpp // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "engine/engine.h"

BaseObject::BaseObject()
{
    pos_x = 0.0;
    pos_y = 0.0;
    type = sprite_t::ST_NONE;
    to_erase = false;
    m_sprite = nullptr;
    m_frame_display_time = 0;
    m_current_frame = 0;
}

BaseObject::BaseObject(double x, double y, sprite_t type)
{
    pos_x = x;
    pos_y = y;
    this->type = type;
    to_erase = false;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(type);
    m_frame_display_time = 0;
    m_current_frame = 0;

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

BaseObject::BaseObject(double x, double y, const SpriteData *sprite)
{
    pos_x = x;
    pos_y = y;
    this->type = type;
    to_erase = false;
    m_sprite = sprite;
    m_frame_display_time = 0;
    m_current_frame = 0;

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

BaseObject::~BaseObject()
{
}

void BaseObject::draw()
{
    if(m_sprite == nullptr || to_erase) return;
	::rect_t src_rect_ = src_rect, dest_rect_ = dest_rect;
    Engine::getEngine().getRenderer()->drawObject(src_rect_, dest_rect_);
}

void BaseObject::update(Uint32 dt)
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
        m_frame_display_time += dt;
        if(m_frame_display_time > m_sprite->frame_duration)
        {
            m_frame_display_time = 0;
            m_current_frame++;
            if(m_current_frame >= m_sprite->frames_count)
            {
                if(m_sprite->loop) m_current_frame = 0;
                else m_current_frame = m_sprite->frames_count - 1;
            }

            src_rect = moveRect(m_sprite->rect, 0, m_current_frame);
        }
    }
}

template<typename T>
rect_t BaseObject::moveRect(const T &rect, int x, int y)
{
    rect_t r;
    r.x = rect.x + x*rect.w;
    r.y = rect.y + y*rect.h;
    r.w = rect.w;
    r.h = rect.h;

    return r;
}
