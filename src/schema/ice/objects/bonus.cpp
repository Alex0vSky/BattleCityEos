// src\schema\ice\objects\bonus.cpp // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "bonus.h"
#include "appconfig.h"

Bonus::Bonus()
    : BaseObject(0, 0, sprite_t::ST_BONUS_STAR)
{
    m_bonus_show_time = 0;
    m_show = true;
}

Bonus::Bonus(double x, double y, SpriteType type)
    : BaseObject(x, y, type)
{
    m_bonus_show_time = 0;
    m_show = true;
}

void Bonus::draw()
{
    if(m_show) BaseObject::draw();
}

void Bonus::update(Uint32 dt)
{
    BaseObject::update(dt);
    m_bonus_show_time += dt;
    if(m_bonus_show_time > AppConfig::bonus_show_time)
        to_erase = true;

    if(m_bonus_show_time / (m_bonus_show_time < AppConfig::bonus_show_time / 4 * 3 ? AppConfig::bonus_blink_time : AppConfig::bonus_blink_time / 2) % 2)
        m_show = true;
    else m_show = false;
}
