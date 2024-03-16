#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
[["underscore"]]

//#include <C:\Prj\syscross\BattleCityEos\src\schema\ice\sliced\custom.h>

/**
 * The Acme module define types and interfaces for game objects
 **/
module Acme {

/**
 * A rectangle, with the origin at the upper left (integer).
 *
 * \sa SDL_RectEmpty
 * \sa SDL_RectEquals
 * \sa SDL_HasIntersection
 * \sa SDL_IntersectRect
 * \sa SDL_IntersectRectAndLine
 * \sa SDL_UnionRect
 * \sa SDL_EnclosePoints
 */
struct SDL_Rect
{
    int x; int y;
    int w; int h;
};

/**
 * The structure that defines a point (integer)
 *
 * \sa SDL_EnclosePoints
 * \sa SDL_PointInRect
 */
struct SDL_Point
{
    int x;
    int y;
};

enum Direction
{
    D_UP = 0,
    D_RIGHT = 1,
    D_DOWN = 2,
    D_LEFT = 3
};

enum TankStateFlag
{
	TSF_DEFAULT = 1, //empty value
	TSF_SHIELD = 2, //after taking the helmet
	TSF_FROZEN = 4, //after the opponent takes the clock
	TSF_DESTROYED = 8, //after taking a bomb from an opponent or being hit by a bullet
	TSF_BOAT = 16, //after taking the boat, allows you to cross the water
	TSF_BONUS = 32, //after hitting this tank, a bonus will appear on the map
	TSF_ON_ICE = 64, //if the tank is on ice, it slides
	TSF_CREATE = 128, //create a tank
	TSF_LIFE = 256,
	TSF_MENU = 512 //speeds up the animation twice
};

enum SpriteType
{
    ST_TANK_A,
    ST_TANK_B,
    ST_TANK_C,
    ST_TANK_D,

    ST_PLAYER_1,
    ST_PLAYER_2,

    ST_BRICK_WALL,
    ST_STONE_WALL,
    ST_WATER,
    ST_BUSH,
    ST_ICE,

    ST_BONUS_GRENADE,
    ST_BONUS_HELMET,
    ST_BONUS_CLOCK,
    ST_BONUS_SHOVEL,
    ST_BONUS_TANK,
    ST_BONUS_STAR,
    ST_BONUS_GUN,
    ST_BONUS_BOAT,

    ST_SHIELD,
    ST_CREATE,
    ST_DESTROY_TANK,
    ST_DESTROY_BULLET,
    ST_BOAT_P1,
    ST_BOAT_P2,

    ST_EAGLE,
    ST_DESTROY_EAGLE,
    ST_FLAG,

    ST_BULLET,

    ST_LEFT_ENEMY,
    ST_STAGE_STATUS,

    ST_TANKS_LOGO,

    ST_NONE
};

/**
 * @brief Base class for game objects
 **/
local class BaseObject {
    /**
     * Display time of the current animation frame.
     */
    ["protected"] int m_frame_display_time;
    /**
     * Number of the current animation frame.
     */
    ["protected"] int m_current_frame;

    /**
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
    bool to_erase;
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    SDL_Rect collision_rect;
    /**
     * The target position of the object on the screen.
     */
    SDL_Rect dest_rect;
    /**
     * Position on the texture of the currently displayed frame.
     */
    SDL_Rect src_rect;
    /**
     * BaseObject type.
     */
    SpriteType type;
    /**
     * Accurate horizontal position of the object.
     */
    double pos_x;
    /**
     * Accurate vertical position of the object.
     */
    double pos_y;
}

["cpp:virtual"]
/**
 * @brief Class dealing with displaying the bonus.
 */
local class Bonus extends BaseObject {
    /**
     * Time since bonus creation.
     */
    ["protected"] int m_bonus_show_time;
    /**
     * Variable storing information about whether the bonus is currently displayed; used for flashing.
     */
    ["protected"] bool m_show;
}

["cpp:virtual"]
/**
 * @brief Class responsible for a single piece of wall.
 * @see BaseObject
 **/
local class Brick extends BaseObject {
    /**
     * Number of times the bullets hit the wall.
     */
    ["protected"] int m_collision_count;
    /**
     * One of the ten states in which a wall can be.
     */
    ["protected"] int m_state_code;
}

["cpp:virtual"]
/**
 * @brief Class dealing with projectiles fired by tanks.
 */
local class Bullet extends BaseObject {
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
}

["cpp:virtual"]
/**
 * @brief An eagle class that players must defend and opponents must destroy.
 */
local class Eagle extends BaseObject {
}

local class Bullet2 {
}
local interface BulletMix2
{
    Bullet2 get();
    void set(Bullet2 bullet);
}

local sequence<BulletMix2> BulletSequence2;

// sequence<BulletMix *> BulletSequence;

["cpp:virtual"]
/**
  * @brief
  * A class dealing with basic tank mechanics: driving, shooting.
  */
local class Tank extends BaseObject {
    /**
     * Flags that the tank currently has.
     */
    ["protected"] TankStateFlag m_flags = TankStateFlag::TSF_DEFAULT;
    /**
     * Time since slippage occurred.
     */
    ["protected"] int m_slip_time;
    /**
     * Corresponds to the direction of the tank in skidding and may be different from the direction of movement of the tank on ice.
     */
    ["protected"] Direction new_direction;
    /**
     * The maximum number of bullets that the tank can fire.
     */
    ["protected"] int m_bullet_max_size;

    /**
     * Time since gaining cover.
     */
    ["protected"] int m_shield_time;
    /**
     * Time since the tank was frozen.
     */
    ["protected"] int m_frozen_time;

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
//    BulletSequence bullets;
	BulletSequence2 bullets;
    /**
     * The number of player lives or the armor level number of the enemy tank.
     */
    int lives_count;
};

["cpp:virtual"]
/**
 * @brief Class dealing with enemy tank movements.
 */
local class Enemy extends Tank {
    /**
     * Time since last change of direction.
     */
    ["protected"] int m_direction_time;
    /**
     * Driving time in a given direction. The time after which the direction will change.
     */
    ["protected"] int m_keep_direction_time;

    /**
     * Time since last attempt to resume driving
     */
    ["protected"] int m_speed_time;
    /**
     * Time after which the next resumption of driving will occur; non-zero speed setting.
     */
    ["protected"] int m_try_to_go_time;

    /**
     * Time since the last missile launch attempt.
     */
    ["protected"] int m_fire_time;
    /**
     * The time after which another shot will be attempted.
     */
    ["protected"] int m_reload_time;

    /**
     * The position to which the enemy tank is heading.
     */
    SDL_Point target_position;
};

["cpp:virtual"]
/**
 * @brief Class corresponding to player tanks.
 */
local class Player extends Tank {
    /**
     * Current number of stars; may be in the range [0, 3].
     */
    ["protected"] int star_count = 0;
    /**
     * The time that has passed since the last missile shot.
     */
    ["protected"] int m_fire_time = 0;
    /**
     * Machine is in movement.
     */
    ["protected"] bool m_movement = false;
    /**
     * It is menu tank.
     */
    ["protected"] bool m_menu = false;

    /**
     * Keys controlling the current player's movements.
     */
//    PlayerKeys player_keys;
    /**
     * The player's current points.
     */
    int score;
};

}