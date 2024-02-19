#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class responsible for a single piece of wall.
 */
class Brick : public Object {
	using PbBrick_t = A0S_proto::PbBrick;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbBrick_t, T, SETTER, GETTER >;
	pb_data_t< PbBrick_t > m_dataOffline{ new PbBrick_t };
	PbBrick_t *m_fieldsDataPointer = m_dataOffline.get( );

	/**
     * Number of times the bullets hit the wall.
     */
	Xetter_t< int, &PbBrick_t::set_collision_count, &PbBrick_t::collision_count > m_collision_count{ m_fieldsDataPointer };
    /**
     * One of the ten states in which a wall can be.
     */
	Xetter_t< int, &PbBrick_t::set_state_code, &PbBrick_t::state_code > m_state_code{ m_fieldsDataPointer };

public:
    /**
     * Creating a wall
     * @param x - horizontal starting position
     * @param y - vertical starting position
     */
    Brick(double x, double y);

    /**
     * The function was implemented not to change collision_rect.
     * @param dt - time since the last function call.
     */
    void update(Uint32 dt);
    /**
     * A function that changes the state of the wall after being hit by a bullet. The function changes collision_rect.
     * @param bullet_direction - bullet direction
     */
    void bulletHit(Direction bullet_direction);
};