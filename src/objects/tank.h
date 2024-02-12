#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "bullet.h"
#include "type.h"

/**
  * @brief
  * A class dealing with basic tank mechanics: driving, shooting.
  */
class Tank : public Object {
protected:
    /**
     * Flags that the tank currently has.
     */
    TankStateFlag m_flags = TankStateFlag::TSF_DEFAULT;
    /**
     * Time since slippage occurred.
     */
    Sint32 m_slip_time;
    /**
     * Corresponds to the direction of the tank in skidding and may be different from the direction of movement of the tank on ice.
     */
    Direction new_direction;
    /**
     * The maximum number of bullets that the tank can fire.
     */
    unsigned m_bullet_max_size;

    /**
     * Pointer to the tank casing. If the tank has no casing, the variable has the value nullptr;
     */
    Object* m_shield;
    /**
     * Pointer to a boat that the tank may have. If the tank does not have a boat, the variable is nullptr;
     */
    Object* m_boat;
    /**
     * Time since gaining cover.
     */
    Uint32 m_shield_time;
    /**
     * Time since the tank was frozen.
     */
    Uint32 m_frozen_time;

public:
    /**
     * Creating a tank in the first enemy position.
     * @see AppConfig::enemy_starting_point
     */
    Tank();
    /**
     * Creating a tank
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - tank type
     */
    Tank(double x, double y, SpriteType type);
    virtual ~Tank();

    /**
     * The function draws an image of a tank, and if necessary, draws a casing and a boat.
     * Triggers bullet drawing.
     */
    void draw();
    /**
     * The function is responsible for changing the position of the tank, updating the position of the dest_rect and collision_rect rectangles, the position of covers and boats, animating the tank,
     * triggering missile updates and removing destroyed missiles. The function counts down the time of cover and freeze and turns off these flags.
     * @param dt - time since the last function call, used when changing the animation
     */
    void update(Uint32 dt);
    /**
     * The function is responsible for creating a projectile if the maximum number of them has not yet been created.
     * @return pointer to the created projectile, if no projectile has been created it returns @a nullptr
     */
    virtual Bullet* fire();
    /**
     * The function returns the collision rectangle that would be in the next frame assuming the current speed and direction.
     * @param dt - expected time to calculate the next frame
     * @return next collision rectangle
     */
    SDL_Rect nextCollisionRect(Uint32 dt);
    /**
     * The function sets the next direction of movement taking into account slippage on ice. When changing direction, the tank is adjusted to a multiple of the dimensions of the @a AppConfig::tile_rect board cell.
     * @param d - new direction
     */
    void setDirection(Direction d);
    /**
     * Function stops the tank.
     * @param intersect_rect - collision area
     */
    void collide(SDL_Rect &intersect_rect);
    /**
     * This function is responsible for clearing all flags and enabling the tank creation animation.
     */
    virtual void respawn();
    /**
     * The function is responsible for turning on the tank explosion animation.
     */
    virtual void destroy();
    /**
     * Set the selected flag.
     * @param flags
     */
    void setFlag(TankStateFlag flag);
    /**
     * Clear selected flag.
     * @param flags
     */
    void clearFlag(TankStateFlag flag);
    /**
     * Checks if the selected flag is set.
     * @param flags
     * @return @a true if the flag is set otherwise @a false
     */
    bool testFlag(TankStateFlag flag);

    /**
     * Default speed of a given tank. It may be different for different types of tanks or may be changed after the player takes the bonus.
     */
    double default_speed;
    /**
     * Current tank speed.
     */
    double speed;
    /**
     * The variable stores information whether the tank is currently stopped.
     */
    bool stop;
    /**
     * Variable stores the current driving direction of the tank.
     */
    Direction direction;
    /**
     * Container with fired tank missiles.
     */
    std::vector<Bullet*> bullets;
    /**
     * The number of player lives or the armor level number of the enemy tank.
     */
    int lives_count;
};
