#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#ifdef A0S_SCHEMA_ICE
#	include "acme.h"
#endif // A0S_SCHEMA_ICE

enum class SpriteType : unsigned char
{
    ST_TANK_A,
    ST_TANK_B,
    ST_TANK_C,
    ST_TANK_D,

    ST_PLAYER_1,
    ST_PLAYER_2,

    ST_BRICK_WALL,
    ST_STONE_WALL,
    ST_WATER,
    ST_BUSH,
    ST_ICE,

    ST_BONUS_GRENADE,
    ST_BONUS_HELMET,
    ST_BONUS_CLOCK,
    ST_BONUS_SHOVEL,
    ST_BONUS_TANK,
    ST_BONUS_STAR,
    ST_BONUS_GUN,
    ST_BONUS_BOAT,

    ST_SHIELD,
    ST_CREATE,
    ST_DESTROY_TANK,
    ST_DESTROY_BULLET,
    ST_BOAT_P1,
    ST_BOAT_P2,

    ST_EAGLE,
    ST_DESTROY_EAGLE,
    ST_FLAG,

    ST_BULLET,

    ST_LEFT_ENEMY,
    ST_STAGE_STATUS,

    ST_TANKS_LOGO,

    ST_NONE
};

#ifdef A0S_SCHEMA_ICE
typedef Acme::SpriteType sprite_t;
#else // A0S_SCHEMA_ICE
typedef SpriteType sprite_t;
#endif // A0S_SCHEMA_ICE

enum class TankStateFlagEnum : int
{
	TSF_DEFAULT = 1 << 0, //empty value
	TSF_SHIELD = 1 << 1, //after taking the helmet
	TSF_FROZEN = 1 << 2, //after the opponent takes the clock
	TSF_DESTROYED = 1 << 3, //after taking a bomb from an opponent or being hit by a bullet
	TSF_BOAT = 1 << 4, //after taking the boat, allows you to cross the water
	TSF_BONUS = 1 << 5, //after hitting this tank, a bonus will appear on the map
	TSF_ON_ICE = 1 << 6, //if the tank is on ice, it slides
	TSF_CREATE = 1 << 7, //create a tank
	TSF_LIFE = 1 << 8,
	TSF_MENU = 1 << 9 //speeds up the animation twice

};
#ifdef A0S_SCHEMA_ICE
typedef Acme::TankStateFlag TankStateFlag;
#else // A0S_SCHEMA_ICE
typedef TankStateFlagEnum TankStateFlag;
#endif // A0S_SCHEMA_ICE

// @insp https://stackoverflow.com/questions/15889414/how-to-overload-operator-on-scoped-enum
inline TankStateFlag operator |(TankStateFlag a, TankStateFlag b) {
    return static_cast<TankStateFlag >(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}
inline TankStateFlag operator |=(TankStateFlag a, TankStateFlag b) {
    return a = a|b;
}
inline TankStateFlag operator &(TankStateFlag a, TankStateFlag b) {
    return static_cast<TankStateFlag >(static_cast<unsigned>(a) & static_cast<unsigned>(b));
}
inline TankStateFlag operator &=(TankStateFlag a, TankStateFlag b) {
    return a = a&b;
}
inline TankStateFlag operator ~(TankStateFlag a) {
    return static_cast<TankStateFlag >(~static_cast<unsigned>(a));
}

enum class DirectionEnum : int
{
    D_UP = 0,
    D_RIGHT = 1,
    D_DOWN = 2,
    D_LEFT = 3
};

#ifdef A0S_SCHEMA_ICE
typedef Acme::Direction Direction;
#else // A0S_SCHEMA_ICE
typedef DirectionEnum Direction;
#endif // A0S_SCHEMA_ICE
