#pragma once // src\schema\ice\objects\tank.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "bullet.h"
#include "type.h"

/**
  * @brief
  * A class dealing with basic tank mechanics: driving, shooting.
  */
class Tank : public BaseObject, public Acme::Tank {
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

	using BaseObject = ::BaseObject;

protected:
    /**
     * Pointer to the tank casing. If the tank has no casing, the variable has the value nullptr;
     */
    BaseObject* m_shield;
    /**
     * Pointer to a boat that the tank may have. If the tank does not have a boat, the variable is nullptr;
     */
    BaseObject* m_boat;

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
    Tank(double x, double y, sprite_t type);
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
     * Container with fired tank missiles.
     */
    std::vector<Bullet*> bullets;
};
