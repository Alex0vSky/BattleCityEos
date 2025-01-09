#pragma once // src\schema\cista\objects\bonus.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with displaying the bonus.
 */
class Bonus : public Object {
    /**
     * Time since bonus creation.
     */
    Uint32 m_bonus_show_time;
    /**
     * Variable storing information about whether the bonus is currently displayed; used for flashing.
     */
    bool m_show;

public:
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
    Bonus(double x, double y, SpriteType type);

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
