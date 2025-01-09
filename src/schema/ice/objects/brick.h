#pragma once // src\schema\ice\objects\brick.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class responsible for a single piece of wall.
 */
class Brick : public BaseObject, public Acme::Brick {
public:
	using Acme::BaseObject::to_erase;
	using Acme::BaseObject::collision_rect;
	using Acme::BaseObject::dest_rect;
	using Acme::BaseObject::src_rect;
	using Acme::BaseObject::type;
	using Acme::BaseObject::pos_x;
	using Acme::BaseObject::pos_y;

    /**
     * Creating a wall at position (0, 0).
     */
    Brick();
    /**
     * Creating a wall
     * @param x - horizontal starting position
     * @param y - vertical starting position
     */
    Brick(double x, double y);

    /**
     * The function was implemented not to change collision_rect.
     * @param dt - time since the last function call.
     */
    void update(Uint32 dt);
    /**
     * A function that changes the state of the wall after being hit by a bullet. The function changes collision_rect.
     * @param bullet_direction - bullet direction
     */
    void bulletHit(Direction bullet_direction);
};