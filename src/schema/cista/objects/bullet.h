#pragma once // src\schema\cista\objects\bullet.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with projectiles fired by tanks.
 */
class Bullet : public Object {
public:
    /**
     * Create a projectile at position (0, 0).
     */
    Bullet();
    /**
     * Create a projectile
     * @param x - horizontal starting position
     * @param y - vertical starting position
     */
    Bullet(double x, double y);

    /**
     * Missile position update.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
    /**
     * Enable missile explosion animation.
     */
    void destroy();
   
    /**
     * Projectile speed.
     */
    double speed;
    /**
     * The variable stores information whether the bullet collided with something.
     */
    bool collide;
    /**
     * The variable stores information whether the bullet has increased damage.
     * Increased damage allows you to destroy stone walls and bushes.
     */
    bool increased_damage;
    /**
     * The direction of the bullet's movement.
     */
    Direction direction;

public:
	auto cista_members() { return std::tie( 
			//*static_cast< Object* >( this )
			speed
			, collide
			, increased_damage
			, direction
		); }
};
