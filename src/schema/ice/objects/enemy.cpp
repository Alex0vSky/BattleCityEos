// src\schema\ice\objects\enemy.cpp // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "enemy.h"
#include "appconfig.h"

Enemy::Enemy()
    : Tank(AppConfig::enemy_starting_point.at(0).x, AppConfig::enemy_starting_point.at(0).y, sprite_t::ST_TANK_A)
{
    direction = Direction::D_DOWN;
    m_direction_time = 0;
    m_keep_direction_time = 100;

    m_speed_time = 0;
    m_try_to_go_time = 100;

    m_fire_time = 0;
    m_reload_time = 100;
    lives_count = 1;

    m_bullet_max_size = 1;

    m_frozen_time = 0;

    if(type == sprite_t::ST_TANK_B)
        default_speed = AppConfig::tank_default_speed * 1.3;
    else
        default_speed = AppConfig::tank_default_speed;

    target_position = {-1, -1};

    respawn();
}

Enemy::Enemy(double x, double y, SpriteType type)
    : Tank(x, y, type)
{
    direction = Direction::D_DOWN;
    m_direction_time = 0;
    m_keep_direction_time = 100;

    m_speed_time = 0;
    m_try_to_go_time = 100;

    m_fire_time = 0;
    m_reload_time = 100;
    lives_count = 1;

    m_bullet_max_size = 1;

    m_frozen_time = 0;

    if(type == sprite_t::ST_TANK_B)
        default_speed = AppConfig::tank_default_speed * 1.3;
    else
        default_speed = AppConfig::tank_default_speed;

    target_position = {-1, -1};

    respawn();
}

void Enemy::draw()
{
    if(to_erase) return;
    if(AppConfig::show_enemy_target)
    {
        SDL_Color c;
        if(type == sprite_t::ST_TANK_A) c = {250, 0, 0, 250};
        if(type == sprite_t::ST_TANK_B) c = {0, 0, 250, 255};
        if(type == sprite_t::ST_TANK_C) c = {0, 255, 0, 250};
        if(type == sprite_t::ST_TANK_D) c = {250, 0, 255, 250};
        SDL_Rect r = {std::min(target_position.x, dest_rect.x + dest_rect.w / 2), dest_rect.y + dest_rect.h / 2, abs(target_position.x - (dest_rect.x + dest_rect.w / 2)), 1};
        Engine::getEngine().getRenderer()->drawRect(&r, c,  true);
        r = {target_position.x, std::min(target_position.y, dest_rect.y + dest_rect.h / 2), 1, abs(target_position.y - (dest_rect.y + dest_rect.h / 2))};
        Engine::getEngine().getRenderer()->drawRect(&r, c, true);
    }
    Tank::draw();
}

void Enemy::update(Uint32 dt)
{
    if(to_erase) return;
    Tank::update(dt);

    if(testFlag(TankStateFlag::TSF_LIFE))
    {
		auto direction_ = static_cast< int >( direction );
		auto new_direction_ = static_cast< int >( new_direction );
        if(testFlag(TankStateFlag::TSF_BONUS))
            src_rect = moveRect( m_sprite ->rect
				, ( testFlag(TankStateFlag::TSF_ON_ICE) ? new_direction_ : direction_ ) - 4
				, m_current_frame );
        else
            src_rect = moveRect( m_sprite->rect
				, ( testFlag(TankStateFlag::TSF_ON_ICE) ? new_direction_ : direction_ ) + ( lives_count -1 ) * 4
				, m_current_frame );
    }
    else
        src_rect = moveRect(m_sprite->rect, 0, m_current_frame);

    if(testFlag(TankStateFlag::TSF_FROZEN)) return;

    m_direction_time += dt;
    m_speed_time += dt;
    m_fire_time += dt;
    if(m_direction_time > m_keep_direction_time)
    {
        m_direction_time = 0;
        m_keep_direction_time = rand() % 800 + 100;

        float p = static_cast<float>(rand()) / RAND_MAX;

        if(p < (type == sprite_t::ST_TANK_A ? 0.8 : 0.5) && target_position.x > 0 && target_position.y > 0)
        {
            int dx = target_position.x - (dest_rect.x + dest_rect.w / 2);
            int dy = target_position.y - (dest_rect.y + dest_rect.h / 2);

            p = static_cast<float>(rand()) / RAND_MAX;

            if(abs(dx) > abs(dy))
                setDirection(p < 0.7 ? (dx < 0 ? Direction::D_LEFT : Direction::D_RIGHT) : (dy < 0 ? Direction::D_UP : Direction::D_DOWN));
            else
                setDirection(p < 0.7 ? (dy < 0 ? Direction::D_UP : Direction::D_DOWN) : (dx < 0 ? Direction::D_LEFT : Direction::D_RIGHT));
        }
        else
            setDirection(static_cast<Direction>(rand() % 4));
    }
    if(m_speed_time > m_try_to_go_time)
    {
        m_speed_time = 0;
        m_try_to_go_time = rand() % 300;
        speed = default_speed;
    }
    if(m_fire_time > m_reload_time)
    {
        m_fire_time = 0;
        if(type == sprite_t::ST_TANK_D)
        {
            m_reload_time = rand() % 400;
            int dx = target_position.x - (dest_rect.x + dest_rect.w / 2);
            int dy = target_position.y - (dest_rect.y + dest_rect.h / 2);

            if(stop) fire();
            else
                switch (direction)
                {
                case Direction::D_UP:
                    if(dy < 0 && abs(dx) < dest_rect.w) fire();
                    break;
                case Direction::D_RIGHT:
                    if(dx > 0 && abs(dy) < dest_rect.h) fire();
                    break;
                case Direction::D_DOWN:
                    if(dy > 0 && abs(dx) < dest_rect.w) fire();
                    break;
                case Direction::D_LEFT:
                    if(dx < 0 && abs(dy) < dest_rect.h) fire();
                    break;
                }
        }
        else if(type == sprite_t::ST_TANK_C)
        {
            m_reload_time = rand() % 800;
            fire();
        }
        else
        {
            m_reload_time = rand() % 1000;
            fire();
        }
    }

    stop = false;
}

void Enemy::destroy()
{
    lives_count--;
//    clearFlag(TSF_BONUS); //it is possible to drop the bonus once
    if(lives_count <= 0)
    {
        lives_count = 0;
        Tank::destroy();
    }
}

unsigned Enemy::scoreForHit()
{
    if(lives_count > 0) return 50;
    return 100;
}
