#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "type.h"
#include "engine/spriteconfig.h"
#include "protobufProxy.h"

/**
 * @brief
 * Base class for game objects.
 */
class Object {
	using PbObject_t = A0S_proto::PbObject;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbObject_t, T, SETTER, GETTER >;
	template<typename OUTER, typename INNER, auto SETTER, auto GETTER>
	using XetterEnum_t = ProxyEnum< PbObject_t, OUTER, INNER, SETTER, GETTER >;
	// TODO(alex): pb_data_t< PbObject_t > m_dataReplicable{ new PbObject_t };
	pb_data_t< PbObject_t > m_dataOffline{ new PbObject_t };
	PbObject_t *m_fieldsDataPointer = m_dataOffline.get( );

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

    /**
     * The function for add new node to replication graph
     * copy previous state
     * replace pointer
     * @param pb_data - new data source
     */
	template<typename T>
	void addToReplicationGraph(pb_data_t<T> & pb_data) {
		*pb_data ->mutable_object( ) = *m_fieldsDataPointer;
		m_fieldsDataPointer = pb_data ->mutable_object( );
	}

public:
	PbObject_t *dataOffline() {
		return m_fieldsDataPointer;
	}
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
	Xetter_t< Uint32, &PbObject_t::set_frame_display_time, &PbObject_t::frame_display_time > frame_display_time{ m_fieldsDataPointer };
    /**
     * Number of the current animation frame.
     */
	Xetter_t< int, &PbObject_t::set_current_frame, &PbObject_t::current_frame > current_frame{ m_fieldsDataPointer };
    /**
     * The variable says whether the object should be deleted. If change is equal to @a true, no updating and drawing of the object is skipped.
     */
	Xetter_t< bool, &PbObject_t::set_to_erase, &PbObject_t::to_erase > to_erase{ m_fieldsDataPointer };
    /**
     * Collision rectangle; may be smaller than the dimensions of dest_rect.
     */
    ProxySdlRect< &PbObject_t::mutable_collision_rect > collision_rect{ m_fieldsDataPointer };
    /**
     * The target position of the object on the screen.
     */
    ProxySdlRect< &PbObject_t::mutable_dest_rect > dest_rect{ m_fieldsDataPointer };
    /**
     * Position on the texture of the currently displayed frame.
     */
    ProxySdlRect< &PbObject_t::mutable_src_rect > src_rect{ m_fieldsDataPointer };
    /**
     * Object type.
     */
	XetterEnum_t< ::SpriteType, A0S_proto::PbSpriteType, &PbObject_t::set_type, &PbObject_t::type > type{ m_fieldsDataPointer };
	/**
	 * Accurate horizontal position of the object.
	 */
	Xetter_t< double, &PbObject_t::set_pos_x, &PbObject_t::pos_x > pos_x{ m_fieldsDataPointer };
	/**
	 * Accurate vertical position of the object.
	 */
	Xetter_t< double, &PbObject_t::set_pos_y, &PbObject_t::pos_y > pos_y{ m_fieldsDataPointer };
};

/**
 * A function that determines the common part of two rectangles
 * @param rect1
 * @param rect2
 * @return common part, if rect1 and rect2 have no common part, the output rectangle will have negative dimensions
 */
SDL_Rect intersectRect(SDL_Rect const& rect1, SDL_Rect const& rect2);
