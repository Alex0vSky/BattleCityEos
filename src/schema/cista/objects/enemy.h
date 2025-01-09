#pragma once // src\schema\cista\objects\enemy.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"
/**
 * @brief Class dealing with enemy tank movements.
 */
class Enemy : public Tank {
    /**
     * Time since last change of direction.
     */
    Uint32 m_direction_time;
    /**
     * Driving time in a given direction. The time after which the direction will change.
     */
    Uint32 m_keep_direction_time;

    /**
     * Time since last attempt to resume driving
     */
    Uint32 m_speed_time;
    /**
     * Time after which the next resumption of driving will occur; non-zero speed setting.
     */
    Uint32 m_try_to_go_time;

    /**
     * Time since the last missile launch attempt.
     */
    Uint32 m_fire_time;
    /**
     * The time after which another shot will be attempted.
     */
    Uint32 m_reload_time;

public:
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
    Enemy(double x, double y, SpriteType type);

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

    /**
     * The position to which the enemy tank is heading.
     */
    point_t target_position;
};
