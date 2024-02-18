#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "type.h"
#include "engine/spriteconfig.h"
#include "protobufProxy.h"

/**
 * @brief
 * Base class for game objects.
 */
class Object {
	using PbObject_t = A0S_proto::Object;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbObject_t, T, SETTER, GETTER >;
	template<typename OUTER, typename INNER, auto SETTER, auto GETTER>
	using XetterEnum_t = ProxyEnum< PbObject_t, OUTER, INNER, SETTER, GETTER >;
	PbObject_t m_dataOffline;
	PbObject_t m_dataReplicable;
	// To easy fallback to replicated and backward (until development)
	PbObject_t &dataOffline() {
		return m_dataOffline;
	}
	PbObject_t &dataReplicable() {
		return m_dataReplicable;
	}

protected:
    /**
     * The function returns a rectangle offset by a multiple of the size of the rect rectangle.
     * @param rect - base rectangle
     * @param x - horizontal offset
     * @param y - vertical offset
     * @return the moved rectangle
     */
    SDL_Rect moveRect(const SDL_Rect &rect, int x, int y);
    SDL_Rect moveRect(const SDL_Rect &rect, Direction x, int y);

    /**
     * Animation corresponding to a given object type.
     */
    const SpriteData* m_sprite;

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
     * Display time of the current animation frame.
     */
	Xetter_t< Uint32, &PbObject_t::set_frame_display_time, &PbObject_t::frame_display_time > frame_display_time{ m_dataOffline };
    /**
     * Number of the current animation frame.
     */
	Xetter_t< int, &PbObject_t::set_current_frame, &PbObject_t::current_frame > current_frame{ m_dataOffline };
    /**
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
	Xetter_t< bool, &PbObject_t::set_to_erase, &PbObject_t::to_erase > to_erase{ m_dataOffline };
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    ProxySdlRect< &PbObject_t::mutable_collision_rect > collision_rect{ m_dataOffline };
    /**
     * The target position of the object on the screen.
     */
    ProxySdlRect< &PbObject_t::mutable_dest_rect > dest_rect{ m_dataOffline };
    /**
     * Position on the texture of the currently displayed frame.
     */
    ProxySdlRect< &PbObject_t::mutable_src_rect > src_rect{ m_dataOffline };
    /**
     * Object type.
     */
	XetterEnum_t< ::SpriteType, A0S_proto::SpriteType, &PbObject_t::set_type, &PbObject_t::type > type{ m_dataOffline };
	/**
	 * Accurate horizontal position of the object.
	 */
	Xetter_t< double, &PbObject_t::set_pos_x, &PbObject_t::pos_x > pos_x{ m_dataReplicable };
	/**
	 * Accurate vertical position of the object.
	 */
	Xetter_t< double, &PbObject_t::set_pos_y, &PbObject_t::pos_y > pos_y{ m_dataReplicable };
};

/**
 * A function that determines the common part of two rectangles
 * @param rect1
 * @param rect2
 * @return common part, if rect1 and rect2 have no common part, the output rectangle will have negative dimensions
 */
SDL_Rect intersectRect(SDL_Rect const& rect1, SDL_Rect const& rect2);
