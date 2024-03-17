#pragma once // src\schema\cista\objects\brick.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class responsible for a single piece of wall.
 */
class Brick : public Object {
    /**
     * Number of times the bullets hit the wall.
     */
    int m_collision_count;
    /**
     * One of the ten states in which a wall can be.
     */
    int m_state_code;

public:
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