#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

[["underscore"]]

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
class BaseObject {

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
//    /**
//     * BaseObject type.
//     */
//    SpriteType type;
    /**
     * Accurate horizontal position of the object.
     */
    double pos_x;
    /**
     * Accurate vertical position of the object.
     */
    double pos_y;
}

/**
 * @brief Class responsible for a single piece of wall.
 * @see BaseObject
 **/
class Brick extends BaseObject {
    /**
     * Number of times the bullets hit the wall.
     */
    int m_collision_count;
}

}