#pragma once // src\schema\ice\objects\eagle.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief An eagle class that players must defend and opponents must destroy.
 */
class Eagle : public BaseObject, public Acme::Eagle {
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

	/**
     * Creating a head at position (0, 0).
     */
    Eagle();
    /**
     * Creating an eagle
     * @param x - horizontal starting position
     * @param y - vertical starting position
     */
    Eagle(double x, double y);
    /**
     * Eagle animation updated.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
    /**
     * Triggering an eagle explosion.
     */
    void destroy();
};
