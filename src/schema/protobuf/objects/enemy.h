#pragma once // src\schema\protobuf\objects\enemy.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"
/**
 * @brief Class dealing with enemy tank movements.
 */
class Enemy : public Tank {
	using PbEnemy_t = A0S_proto::PbEnemy;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbEnemy_t, T, SETTER, GETTER >;
	pb_data_t< PbEnemy_t > m_dataOffline{ new PbEnemy_t };
	PbEnemy_t *m_fieldsDataPointer = m_dataOffline.get( );

    /**
     * Time since last change of direction.
     */
	Xetter_t< Uint32, &PbEnemy_t::set_direction_time, &PbEnemy_t::direction_time > m_direction_time{ m_fieldsDataPointer };
    /**
     * Driving time in a given direction. The time after which the direction will change.
     */
	Xetter_t< Uint32, &PbEnemy_t::set_keep_direction_time, &PbEnemy_t::keep_direction_time > m_keep_direction_time{ m_fieldsDataPointer };

    /**
     * Time since last attempt to resume driving
     */
	Xetter_t< Uint32, &PbEnemy_t::set_speed_time, &PbEnemy_t::speed_time > m_speed_time{ m_fieldsDataPointer };
    /**
     * Time after which the next resumption of driving will occur; non-zero speed setting.
     */
	Xetter_t< Uint32, &PbEnemy_t::set_try_to_go_time, &PbEnemy_t::try_to_go_time > m_try_to_go_time{ m_fieldsDataPointer };

    /**
     * Time since the last missile launch attempt.
     */
	Xetter_t< Uint32, &PbEnemy_t::set_fire_time, &PbEnemy_t::fire_time > m_fire_time{ m_fieldsDataPointer };
    /**
     * The time after which another shot will be attempted.
     */
	Xetter_t< Uint32, &PbEnemy_t::set_reload_time, &PbEnemy_t::reload_time > m_reload_time{ m_fieldsDataPointer };

public:
    /**
     * Create an opponent
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - type of enemy tank
     */
    Enemy(double x, double y, sprite_t type);

    /**
     * The function draws the enemy tank and if the @a AppConfig::show_enemy_target flag is set, I draw a line connecting the tank with its target.
     */
    void draw();
    /**
     * The function updates the tank's position and decides the direction and time of the next shot depending on the enemy type.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
    /**
     * Reducing the armor level by 1. If the armor level reaches zero, the tank explodes (destructs).
     */
    void destroy();
    /**
     * The function returns the number of points the player will receive for hitting a given enemy tank.
     * @return points
     */
    unsigned scoreForHit();

    /**
     * The position to which the enemy tank is heading.
     */
	ProxySdlPoint< PbEnemy_t, &PbEnemy_t::mutable_target_position > target_position{ m_fieldsDataPointer };
};
