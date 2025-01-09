#pragma once // src\schema\protobuf\objects\bullet.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"

/**
 * @brief Class dealing with projectiles fired by tanks.
 */
class Bullet : public Object {
	using PbBullet_t = A0S_proto::PbBullet;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbBullet_t, T, SETTER, GETTER >;
	template<typename OUTER, typename INNER, auto SETTER, auto GETTER>
	using XetterEnum_t = ProxyEnum< PbBullet_t, OUTER, INNER, SETTER, GETTER >;
	pb_data_t< PbBullet_t > m_dataOffline{ new PbBullet_t };
	PbBullet_t *m_fieldsDataPointer = m_dataOffline.get( );

	template<typename, typename, typename, auto, typename> 
	friend class ProxyVector;
	void replaceFieldsDataPointer(PbBullet_t *bullet) {
		Object::replaceFieldsDataPointer( bullet ->mutable_object( ) );
		m_fieldsDataPointer = bullet;
	}
	PbBullet_t *getFieldsDataPointer() {
		return m_fieldsDataPointer;
	}

public:
    /**
     * Create a projectile
     * @param x - horizontal starting position
     * @param y - vertical starting position
     */
    Bullet(double x, double y);

    /**
     * Missile position update.
     * @param dt - time since the last function call
     */
    void update(Uint32 dt);
    /**
     * Enable missile explosion animation.
     */
    void destroy();
   
    /**
     * Projectile speed.
     */
	Xetter_t< double, &PbBullet_t::set_speed, &PbBullet_t::speed > speed{ m_fieldsDataPointer };
    /**
     * The variable stores information whether the bullet collided with something.
     */
	Xetter_t< bool, &PbBullet_t::set_collide, &PbBullet_t::collide > collide{ m_fieldsDataPointer };
    /**
     * The variable stores information whether the bullet has increased damage.
     * Increased damage allows you to destroy stone walls and bushes.
     */
	Xetter_t< bool, &PbBullet_t::set_increased_damage, &PbBullet_t::increased_damage > increased_damage{ m_fieldsDataPointer };
    /**
     * The direction of the bullet's movement.
     */
	XetterEnum_t< ::Direction, A0S_proto::PbDirection, &PbBullet_t::set_direction, &PbBullet_t::direction > direction{ m_fieldsDataPointer };
};
