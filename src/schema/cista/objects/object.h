#pragma once // src\schema\cista\objects\object.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "type.h"
#include "engine/spriteconfig.h"

/**
 * @brief
 * Base class for game objects.
 */
class Object {
protected:
    /**
     * The function returns a rectangle offset by a multiple of the size of the rect rectangle.
     * @param rect - base rectangle
     * @param x - horizontal offset
     * @param y - vertical offset
     * @return the moved rectangle
     */
    rect_t moveRect(const rect_t &rect, int x, int y);

public: // tmp
    /**
     * Animation corresponding to a given object type.
     */
    SpriteDataWrapper m_sprite;
protected: // tmp
    /**
     * Display time of the current animation frame.
     */
    Uint32 m_frame_display_time;
    /**
     * Number of the current animation frame.
     */
    int m_current_frame;

public:
    /**
     * Create an object at position (0, 0).
     */
    Object();
    /**
     * Create an object.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - the type of the object
     */
    Object(double x, double y, SpriteType type);
    /**
     * Create an object.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param sprite - animation of an object of a given type
     */
    Object(double x, double y, const SpriteData* sprite);
    virtual ~Object();

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
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
    bool to_erase;
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    rect_t collision_rect;
    /**
     * The target position of the object on the screen.
     */
    rect_t dest_rect;
    /**
     * Position on the texture of the currently displayed frame.
     */
    rect_t src_rect;
    /**
     * Object type.
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

public:
	auto cista_members() { return std::tie( 
			m_frame_display_time
			, m_sprite
			, m_current_frame
			, to_erase
			, collision_rect
			, dest_rect
			, src_rect
			, type
			, pos_x
			, pos_y
		); }
};

/**
 * A function that determines the common part of two rectangles
 * @param rect1
 * @param rect2
 * @return common part, if rect1 and rect2 have no common part, the output rectangle will have negative dimensions
 */
rect_t intersectRect(rect_t const& rect1, rect_t const& rect2);
