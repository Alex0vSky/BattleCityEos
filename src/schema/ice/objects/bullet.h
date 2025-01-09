#pragma once // src\schema\ice\objects\bullet.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with projectiles fired by tanks.
 */
class Bullet : public BaseObject, public Acme::Bullet {
protected:
	using Acme::BaseObject::m_frame_display_time;
	using Acme::BaseObject::m_current_frame;

public:			
	using Acme::BaseObject::to_erase;
	using Acme::BaseObject::collision_rect;
	using Acme::BaseObject::dest_rect;
	using Acme::BaseObject::src_rect;
	using Acme::BaseObject::type;
	using Acme::BaseObject::pos_x;
	using Acme::BaseObject::pos_y;


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
};
