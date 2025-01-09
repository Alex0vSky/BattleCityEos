#pragma once // src\schema\ice\objects\bonus.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with displaying the bonus.
 */
class Bonus : public BaseObject, public Acme::Bonus {
public:
	using Acme::BaseObject::to_erase;
	using Acme::BaseObject::collision_rect;
	using Acme::BaseObject::dest_rect;
	using Acme::BaseObject::src_rect;
	using Acme::BaseObject::type;
	using Acme::BaseObject::pos_x;
	using Acme::BaseObject::pos_y;

    /**
     * Creating a default bonus - stars at position (0, 0).
     */
    Bonus();
    /**
     *Creating a bonus.
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - bonus type
     */
    Bonus(double x, double y, sprite_t type);

    /**
     * Bonus drawing function.
     */
    void draw();
    /**
     * Feature updating bonus animations. Permission to delete after a reasonable period of time.
     * Increased flashing frequency if the bonus is about to be removed.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
};
