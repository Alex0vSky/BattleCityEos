#pragma once // src\schema\ice\objects\enemy.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"
/**
 * @brief Class dealing with enemy tank movements.
 */
class Enemy : public Tank, public Acme::Enemy {
protected:
	using Acme::BaseObject::m_frame_display_time;
	using Acme::BaseObject::m_current_frame;

	using Acme::Tank::m_flags;
    using Acme::Tank::m_slip_time;
    using Acme::Tank::new_direction;
    using Acme::Tank::m_bullet_max_size;
    using Acme::Tank::m_shield_time;
    using Acme::Tank::m_frozen_time;

public:
	using Acme::BaseObject::to_erase;
	using Acme::BaseObject::collision_rect;
	using Acme::BaseObject::dest_rect;
	using Acme::BaseObject::src_rect;
	using Acme::BaseObject::type;
	using Acme::BaseObject::pos_x;
	using Acme::BaseObject::pos_y;

    using Acme::Tank::default_speed;
    using Acme::Tank::speed;
    using Acme::Tank::stop;
    using Acme::Tank::direction;
    //using Acme::Tank::bullets;
    using Tank::bullets;
    using Acme::Tank::lives_count;

	using BaseObject = ::BaseObject;

	/**
     * Creating an enemy in the first enemy position.
     * @see AppConfig::enemy_starting_point
     */
    Enemy();
    /**
     * Create an opponent
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - type of enemy tank
     */
    Enemy(double x, double y, sprite_t type);

    /**
     * The function draws the enemy tank and if the @a AppConfig::show_enemy_target flag is set, I draw a line connecting the tank with its target.
     */
    void draw();
    /**
     * The function updates the tank's position and decides the direction and time of the next shot depending on the enemy type.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
    /**
     * Reducing the armor level by 1. If the armor level reaches zero, the tank explodes (destructs).
     */
    void destroy();
    /**
     * The function returns the number of points the player will receive for hitting a given enemy tank.
     * @return points
     */
    unsigned scoreForHit();
};
