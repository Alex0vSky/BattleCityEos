#pragma once // src\schema\ice\objects\eagle.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief An eagle class that players must defend and opponents must destroy.
 */
class Eagle : public BaseObject {
public:
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
