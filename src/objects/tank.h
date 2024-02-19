#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "object.h"
#include "bullet.h"
#include "type.h"

/**
  * @brief
  * A class dealing with basic tank mechanics: driving, shooting.
  */
class Tank : public Object {
	using PbTank_t = A0S_proto::PbTank;
	template<typename T, auto SETTER, auto GETTER>
	using Xetter_t = ProxyXetter< PbTank_t, T, SETTER, GETTER >;
	template<typename OUTER, typename INNER, auto SETTER, auto GETTER>
	using XetterEnum_t = ProxyEnum< PbTank_t, OUTER, INNER, SETTER, GETTER >;
	pb_data_t< PbTank_t > m_dataOffline{ new PbTank_t };
	PbTank_t *m_fieldsDataPointer = m_dataOffline.get( );

protected:
    /**
     * Flags that the tank currently has.
     */
	XetterEnum_t< ::TankStateFlag, A0S_proto::PbTankStateFlag, &PbTank_t::set_flags, &PbTank_t::flags > m_flags{ m_fieldsDataPointer };
    /**
     * Time since slippage occurred.
     */
	Xetter_t< Sint32, &PbTank_t::set_slip_time, &PbTank_t::slip_time > m_slip_time{ m_fieldsDataPointer };
    /**
     * Corresponds to the direction of the tank in skidding and may be different from the direction of movement of the tank on ice.
     */
	XetterEnum_t< ::Direction, A0S_proto::PbDirection, &PbTank_t::set_new_direction, &PbTank_t::new_direction > new_direction{ m_fieldsDataPointer };
    /**
     * The maximum number of bullets that the tank can fire.
     */
	Xetter_t< Uint32, &PbTank_t::set_bullet_max_size, &PbTank_t::bullet_max_size > m_bullet_max_size{ m_fieldsDataPointer };

    /**
     * Pointer to the tank casing. If the tank has no casing, the variable has the value nullptr;
     */
    Object* m_shield;
    /**
     * Pointer to a boat that the tank may have. If the tank does not have a boat, the variable is nullptr;
     */
    Object* m_boat;
    /**
     * Time since gaining cover.
     */
	Xetter_t< Uint32, &PbTank_t::set_shield_time, &PbTank_t::shield_time > m_shield_time{ m_fieldsDataPointer };
    /**
     * Time since the tank was frozen.
     */
	Xetter_t< Uint32, &PbTank_t::set_frozen_time, &PbTank_t::frozen_time > m_frozen_time{ m_fieldsDataPointer };

public:
    /**
     * Creating a tank
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - tank type
     */
    Tank(double x, double y, SpriteType type);
    virtual ~Tank();

    /**
     * The function draws an image of a tank, and if necessary, draws a casing and a boat.
     * Triggers bullet drawing.
     */
    void draw();
    /**
     * The function is responsible for changing the position of the tank, updating the position of the dest_rect and collision_rect rectangles, the position of covers and boats, animating the tank,
     * triggering missile updates and removing destroyed missiles. The function counts down the time of cover and freeze and turns off these flags.
     * @param dt - time since the last function call, used when changing the animation
     */
    void update(Uint32 dt);
    /**
     * The function is responsible for creating a projectile if the maximum number of them has not yet been created.
     * @return pointer to the created projectile, if no projectile has been created it returns @a nullptr
     */
    virtual Bullet* fire();
    /**
     * The function returns the collision rectangle that would be in the next frame assuming the current speed and direction.
     * @param dt - expected time to calculate the next frame
     * @return next collision rectangle
     */
    SDL_Rect nextCollisionRect(Uint32 dt);
    /**
     * The function sets the next direction of movement taking into account slippage on ice. When changing direction, the tank is adjusted to a multiple of the dimensions of the @a AppConfig::tile_rect board cell.
     * @param d - new direction
     */
    void setDirection(Direction d);
    /**
     * Function stops the tank.
     * @param intersect_rect - collision area
     */
    void collide(SDL_Rect &intersect_rect);
    /**
     * This function is responsible for clearing all flags and enabling the tank creation animation.
     */
    virtual void respawn();
    /**
     * The function is responsible for turning on the tank explosion animation.
     */
    virtual void destroy();
    /**
     * Set the selected flag.
     * @param flags
     */
    void setFlag(TankStateFlag flag);
    /**
     * Clear selected flag.
     * @param flags
     */
    void clearFlag(TankStateFlag flag);
    /**
     * Checks if the selected flag is set.
     * @param flags
     * @return @a true if the flag is set otherwise @a false
     */
    bool testFlag(TankStateFlag flag);

    /**
     * Default speed of a given tank. It may be different for different types of tanks or may be changed after the player takes the bonus.
     */
	Xetter_t< double, &PbTank_t::set_default_speed, &PbTank_t::default_speed > default_speed{ m_fieldsDataPointer };
    /**
     * Current tank speed.
     */
	Xetter_t< double, &PbTank_t::set_speed, &PbTank_t::speed > speed{ m_fieldsDataPointer };
    /**
     * The variable stores information whether the tank is currently stopped.
     */
	Xetter_t< bool, &PbTank_t::set_stop, &PbTank_t::stop > stop{ m_fieldsDataPointer };
    /**
     * Variable stores the current driving direction of the tank.
     */
	XetterEnum_t< ::Direction, A0S_proto::PbDirection, &PbTank_t::set_direction, &PbTank_t::direction > direction{ m_fieldsDataPointer };
    /**
     * Container with fired tank missiles.
     */
    std::vector<Bullet*> bullets;
	//ProxyVector< 
	//		PbTank_t 
	//		, Bullet *
	//		, A0S_proto::PbBullet 
	//		, ( google::protobuf::RepeatedPtrField<A0S_proto::PbBullet>*(PbTank_t::*)() ) &PbTank_t::mutable_bullets 
	//	> bullets{ m_fieldsDataPointer };
    /**
     * The number of player lives or the armor level number of the enemy tank.
     */
	Xetter_t< int, &PbTank_t::set_lives_count, &PbTank_t::lives_count > lives_count{ m_fieldsDataPointer };
};
