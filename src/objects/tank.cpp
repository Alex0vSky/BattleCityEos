// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"
#include "appconfig.h"

Tank::Tank()
    : Object(AppConfig::enemy_starting_point.at(0).x, AppConfig::enemy_starting_point.at(0).y, ST_TANK_A)
{
    direction = D_UP;
    m_slip_time = 0;
    default_speed = AppConfig::tank_default_speed;
    speed = 0.0;
    m_shield = nullptr;
    m_boat = nullptr;
    m_shield_time = 0;
    m_frozen_time = 0;
}

Tank::Tank(double x, double y, SpriteType type)
    : Object(x, y, type)
{
    direction = D_UP;
    m_slip_time = 0;
    default_speed = AppConfig::tank_default_speed;
    speed = 0.0;
    m_shield = nullptr;
    m_boat = nullptr;
    m_shield_time = 0;
    m_frozen_time = 0;
}

Tank::~Tank()
{
    for(auto bullet : bullets) delete bullet;
    bullets.clear();

    if(m_shield != nullptr)
    {
        delete m_shield;
        m_shield = nullptr;
    }
    if(m_boat != nullptr)
    {
        delete m_boat;
        m_boat = nullptr;
    }
}

void Tank::draw()
{
    if(to_erase) return;
    Object::draw();

    if(testFlag(TankStateFlag::TSF_SHIELD) && m_shield != nullptr) m_shield->draw();
    if(testFlag(TankStateFlag::TSF_BOAT) && m_boat != nullptr) m_boat->draw();

    for(auto bullet : bullets)
        if(bullet != nullptr) bullet->draw();
}

void Tank::update(Uint32 dt)
{
    if(to_erase) return;
    if(testFlag(TankStateFlag::TSF_LIFE))
    {
        if(!stop && !testFlag(TankStateFlag::TSF_FROZEN))
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
        }

        dest_rect.x = dataReplicable( ).pos_x( );
        dest_rect.y = dataReplicable( ).pos_y( );
        dest_rect.h = m_sprite->rect.h;
        dest_rect.w = m_sprite->rect.w;

        collision_rect.x = dest_rect.x + 2;
        collision_rect.y = dest_rect.y + 2;
        collision_rect.h = dest_rect.h - 4;
        collision_rect.w = dest_rect.w - 4;
    }

    if(testFlag(TankStateFlag::TSF_ON_ICE) && m_slip_time > 0)
    {
        m_slip_time -= dt;
        if(m_slip_time <= 0)
        {
            clearFlag(TankStateFlag::TSF_ON_ICE);
            m_slip_time = 0;
            direction = new_direction;
        }
    }

    if(testFlag(TankStateFlag::TSF_SHIELD) && m_shield != nullptr)
    {
        m_shield_time += dt;
        m_shield ->dataReplicable( ).set_pos_x( dataReplicable( ).pos_x( ) );
        m_shield ->dataReplicable( ).set_pos_y( dataReplicable( ).pos_y( ) );
        m_shield->update(dt);
        if(m_shield_time > AppConfig::tank_shield_time) clearFlag(TankStateFlag::TSF_SHIELD);
    }
    if(testFlag(TankStateFlag::TSF_BOAT) && m_boat != nullptr)
    {
        m_boat ->dataReplicable( ).set_pos_x( dataReplicable( ).pos_x( ) );
        m_boat ->dataReplicable( ).set_pos_y( dataReplicable( ).pos_y( ) );
        m_boat->update(dt);
    }
    if(testFlag(TankStateFlag::TSF_FROZEN))
    {
        m_frozen_time += dt;
        if(m_frozen_time > AppConfig::tank_frozen_time) clearFlag(TankStateFlag::TSF_FROZEN);
    }

    if(m_sprite->frames_count > 1 && (testFlag(TankStateFlag::TSF_LIFE) ? speed > 0 : true)) //no animation if the tank is not trying to move
    {
		dataOffline( ).set_frame_display_time( dataOffline( ).frame_display_time( ) + dt );
        if( 
			dataOffline( ).frame_display_time( ) 
			> 
			(testFlag(TankStateFlag::TSF_MENU)  ? m_sprite->frame_duration / 2 : m_sprite->frame_duration)
		)
        {
			dataOffline( ).set_frame_display_time( 0 );
			dataOffline( ).set_current_frame( dataOffline( ).current_frame( ) + 1 );
			if ( dataOffline( ).current_frame( ) >= m_sprite ->frames_count )
            {
                if ( m_sprite ->loop ) dataOffline( ).set_current_frame( 0 );
                else if(testFlag(TankStateFlag::TSF_CREATE))
                {
                    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(type);
                    clearFlag(TankStateFlag::TSF_CREATE);
                    setFlag(TankStateFlag::TSF_LIFE);
					dataOffline( ).set_current_frame( 0 );
                }
                else if(testFlag(TankStateFlag::TSF_DESTROYED))
                {
					dataOffline( ).set_current_frame( m_sprite->frames_count );
                    if(lives_count > 0) respawn();
                    else if(bullets.size() == 0) to_erase = true;
                }
            }
        }
    }


    // Missile handling
    for(auto bullet : bullets) bullet->update(dt);
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet*b){if(b->to_erase) {delete b; return true;} return false;}), bullets.end());
}

Bullet* Tank::fire()
{
    if(!testFlag(TankStateFlag::TSF_LIFE)) return nullptr;
    if(bullets.size() < m_bullet_max_size)
    {
        //we enter an arbitrary initial position because we do not know the dimensions of the projectile
        Bullet* bullet = new Bullet( dataReplicable( ).pos_x( ), dataReplicable( ).pos_y( ) );
        bullets.push_back(bullet);

        Direction tmp_d = (testFlag(TankStateFlag::TSF_ON_ICE) ? new_direction : direction);
        switch(tmp_d)
        {
        case D_UP:
	        bullet ->dataReplicable( ).set_pos_x( 
					bullet ->dataReplicable( ).pos_x( ) 
					+ ( (dest_rect.w - bullet->dest_rect.w) / 2 )
				);
	        bullet ->dataReplicable( ).set_pos_y( 
					bullet ->dataReplicable( ).pos_y( ) 
					- ( bullet->dest_rect.h - 4 )
				);
            break;
        case D_RIGHT:
	        bullet ->dataReplicable( ).set_pos_x( 
					bullet ->dataReplicable( ).pos_x( ) 
					+ ( dest_rect.w - 4 )
				);
	        bullet ->dataReplicable( ).set_pos_y( 
					bullet ->dataReplicable( ).pos_y( ) 
					+ ( (dest_rect.h - bullet->dest_rect.h) / 2 )
				);
            break;
        case D_DOWN:
	        bullet ->dataReplicable( ).set_pos_x( 
					bullet ->dataReplicable( ).pos_x( ) 
					+ ( (dest_rect.w - bullet->dest_rect.w) / 2 )
				);
	        bullet ->dataReplicable( ).set_pos_y( 
					bullet ->dataReplicable( ).pos_y( ) 
					+ ( dest_rect.h - 4 )
				);
            break;
        case D_LEFT:
	        bullet ->dataReplicable( ).set_pos_x( 
					bullet ->dataReplicable( ).pos_x( ) 
					- ( bullet->dest_rect.w - 4 )
				);
	        bullet ->dataReplicable( ).set_pos_y( 
					bullet ->dataReplicable( ).pos_y( ) 
					+ ( (dest_rect.h - bullet->dest_rect.h) / 2 )
				);
            break;
        }

        bullet->direction = tmp_d;
        if(type == ST_TANK_C)
            bullet->speed = AppConfig::bullet_default_speed * 1.3;
        else
            bullet->speed = AppConfig::bullet_default_speed;

        bullet->update(0); //change position of dest_rect
		Engine::getEngine( ).getAudio( ) ->playSound( ) ->fire( );
        return bullet;
    }
    return nullptr;
}

SDL_Rect Tank::nextCollisionRect(Uint32 dt)
{
    if(speed == 0) return collision_rect;

    SDL_Rect r;
    int a = 1;
    switch (direction)
    {
    case D_UP:
        r.x = collision_rect.x;
        r.y = collision_rect.y - default_speed * dt - a;
        break;
    case D_RIGHT:
        r.x = collision_rect.x + default_speed * dt + a;
        r.y = collision_rect.y;
        break;
    case D_DOWN:
        r.x = collision_rect.x;
        r.y = collision_rect.y + default_speed * dt + a;
        break;
    case D_LEFT:
        r.x = collision_rect.x - default_speed * dt - a;
        r.y = collision_rect.y;
        break;
    }
    r.h = collision_rect.h;
    r.w = collision_rect.w;

    return r;
}

void Tank::setDirection(Direction d)
{
    if(!(testFlag(TankStateFlag::TSF_LIFE) || testFlag(TankStateFlag::TSF_CREATE))) return;
    if(testFlag(TankStateFlag::TSF_ON_ICE))
    {
        new_direction = d;
        if(speed == 0.0 || m_slip_time == 0.0) direction = d;
        if((m_slip_time != 0 && direction == new_direction) || m_slip_time == 0)
            m_slip_time = AppConfig::slip_time;
    }
    else
        direction = d;

    if(!stop)
    {
        double epsilon = 5;
        int pos_x_tile, pos_y_tile;
        switch (direction)
        {
        case D_UP:
        case D_DOWN:
            pos_x_tile = ((int)( dataReplicable( ).pos_x( ) / AppConfig::tile_rect.w)) * AppConfig::tile_rect.w;
            if( dataReplicable( ).pos_x( ) - pos_x_tile < epsilon) dataReplicable( ).set_pos_x( pos_x_tile );
            else if(pos_x_tile + AppConfig::tile_rect.w - dataReplicable( ).pos_x( ) < epsilon) dataReplicable( ).set_pos_x( pos_x_tile + AppConfig::tile_rect.w );
            break;
        case D_RIGHT:
        case D_LEFT:
            pos_y_tile = ((int)( dataReplicable( ).pos_y( ) / AppConfig::tile_rect.h)) * AppConfig::tile_rect.h;
            if( dataReplicable( ).pos_y( ) - pos_y_tile < epsilon) dataReplicable( ).set_pos_y( pos_y_tile );
            else if(pos_y_tile + AppConfig::tile_rect.h - dataReplicable( ).pos_y( ) < epsilon) dataReplicable( ).set_pos_y( pos_y_tile + AppConfig::tile_rect.h );
            break;
        }
    }
}

void Tank::collide(SDL_Rect &intersect_rect)
{
    if(intersect_rect.w > intersect_rect.h) // collision from above or below
    {
        if((direction == D_UP && intersect_rect.y <= collision_rect.y) ||
                (direction == D_DOWN && (intersect_rect.y + intersect_rect.h) >= (collision_rect.y + collision_rect.h)))
        {
            stop = true;
            m_slip_time = 0;
        }
    }
    else
    {
        if((direction == D_LEFT && intersect_rect.x <= collision_rect.x) ||
                (direction == D_RIGHT && (intersect_rect.x + intersect_rect.w) >= (collision_rect.x + collision_rect.w)))
        {
            stop = true;
            m_slip_time = 0;
        }
    }
}

void Tank::destroy()
{
    if(!testFlag(TankStateFlag::TSF_LIFE)) return;

    stop = true;
    m_flags = TankStateFlag::TSF_DESTROYED;

	dataOffline( ).set_frame_display_time( 0 );
	dataOffline( ).set_current_frame( 0 );
    direction = D_UP;
    speed = 0;
    m_slip_time = 0;
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_DESTROY_TANK);

    collision_rect.x = 0;
    collision_rect.y = 0;
    collision_rect.h = 0;
    collision_rect.w = 0;

    dest_rect.x = dataReplicable( ).pos_x( ) + (dest_rect.w - m_sprite->rect.w)/2;
    dest_rect.y = dataReplicable( ).pos_y( ) + (dest_rect.h - m_sprite->rect.h)/2;
    dest_rect.h = m_sprite->rect.h;
    dest_rect.w = m_sprite->rect.w;
	Engine::getEngine( ).getAudio( ) ->playSound( ) ->die( );
}

void Tank::setFlag(TankStateFlag flag)
{
    if(!testFlag(flag) && flag == TankStateFlag::TSF_ON_ICE)
        new_direction = direction;

    if(flag == TankStateFlag::TSF_SHIELD)
    {
        if(m_shield == nullptr) m_shield = new Object( dataReplicable( ).pos_x( ), dataReplicable( ).pos_y( ), ST_SHIELD);
         m_shield_time = 0;
    }
    if(flag == TankStateFlag::TSF_BOAT)
    {
         if(m_boat == nullptr) m_boat = new Object( dataReplicable( ).pos_x( ), dataReplicable( ).pos_y( ), type == ST_PLAYER_1 ? ST_BOAT_P1 : ST_BOAT_P2);
    }
    if(flag == TankStateFlag::TSF_FROZEN)
    {
        m_frozen_time = 0;
    }
    m_flags = m_flags | flag;
}

void Tank::clearFlag(TankStateFlag flag)
{
    if(flag == TankStateFlag::TSF_SHIELD)
    {
         if(m_shield != nullptr) delete m_shield;
         m_shield = nullptr;
         m_shield_time = 0;
    }
    if(flag == TankStateFlag::TSF_BOAT)
    {
         if(m_boat != nullptr) delete m_boat;
         m_boat = nullptr;
    }
    if(flag == TankStateFlag::TSF_FROZEN)
    {
        m_frozen_time = 0;
    }
    m_flags = m_flags & (~flag);
}

bool Tank::testFlag(TankStateFlag flag)
{
    return (m_flags & flag) == flag;
}

void Tank::respawn()
{
    m_sprite = Engine::getEngine().getSpriteConfig()->getSpriteData(ST_CREATE);
    speed = 0.0;
    stop = false;
    m_slip_time = 0;

    clearFlag(TankStateFlag::TSF_SHIELD);
    clearFlag(TankStateFlag::TSF_BOAT);
    m_flags = TankStateFlag::TSF_LIFE;
    update(0);
    m_flags = TankStateFlag::TSF_CREATE; //reset all other flags

    //setting the collision angle after calling update
    collision_rect.x = 0;
    collision_rect.y = 0;
    collision_rect.h = 0;
    collision_rect.w = 0;
}
