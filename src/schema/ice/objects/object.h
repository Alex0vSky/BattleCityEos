#pragma once // src\schema\ice\objects\object.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "type.h"
#include "engine/spriteconfig.h"
#include "acme.h"

/**
 * @brief
 * Base class for game objects.
 * Named like BaseObject due for zeroc.ice: keyword `Object' cannot be used as class name
 */
class BaseObject : public Acme::BaseObject {
protected:
    /**
     * The function returns a rectangle offset by a multiple of the size of the rect rectangle.
     * @param rect - base rectangle
     * @param x - horizontal offset
     * @param y - vertical offset
     * @return the moved rectangle
     */
	template<typename T>
	Acme::SDL_Rect moveRect(const T &rect, int x, int y);

    /**
     * Animation corresponding to a given object type.
     */
    const SpriteData* m_sprite;

public:
    /**
     * Create an object at position (0, 0).
     */
    BaseObject();
    /**
     * Create an object.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - the type of the object
     */
    BaseObject(double x, double y, SpriteType type);
    /**
     * Create an object.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param sprite - animation of an object of a given type
     */
    BaseObject(double x, double y, const SpriteData* sprite);
    virtual ~BaseObject();

    /**
     * Drawing, using the @a drawObject method of the @a Renderer class, a texture object with src_rect coordinates to a map area with dest_rect coordinates.
     */
    virtual void draw();
    /**
     * Update dest_rect based on object position: pos_x, pos_y. Countdown the display time of one animation frame and change the frame after counting down the appropriate time.
     * @param dt - time since the last function call, used to count down the frame display time
     */
    virtual void update(Uint32 dt);

    /**
     * BaseObject type.
     */
    SpriteType type;
};

/**
 * A function that determines the common part of two rectangles
 * @param rect1
 * @param rect2
 * @return common part, if rect1 and rect2 have no common part, the output rectangle will have negative dimensions
 */
template<typename T1, typename T2>
SDL_Rect intersectRect(T1 const& rect1, T2 const& rect2)
{
    SDL_Rect intersect_rect;
    intersect_rect.x = std::max(rect1.x, rect2.x);
    intersect_rect.y = std::max(rect1.y, rect2.y);
    intersect_rect.w = std::min(rect1.x + rect1.w, rect2.x + rect2.w) - intersect_rect.x;
    intersect_rect.h = std::min(rect1.y + rect1.h, rect2.y + rect2.h) - intersect_rect.y;

    return intersect_rect;
}

#define spriteType_t
