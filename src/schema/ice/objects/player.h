#pragma once // src\schema\ice\objects\player.h // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"

/**
 * @brief Class corresponding to player tanks.
 */
class Player : public Tank, public Acme::Player {
protected:
	using Acme::BaseObject::m_frame_display_time;
	using Acme::BaseObject::m_current_frame;

	using Acme::Tank::m_flags;
    using Acme::Tank::m_slip_time;
    using Acme::Tank::new_direction;
    using Acme::Tank::m_bullet_max_size;
    using Acme::Tank::m_shield_time;
    using Acme::Tank::m_frozen_time;

public:
	using Acme::BaseObject::to_erase;
	using Acme::BaseObject::collision_rect;
	using Acme::BaseObject::dest_rect;
	using Acme::BaseObject::src_rect;
	using Acme::BaseObject::type;
	using Acme::BaseObject::pos_x;
	using Acme::BaseObject::pos_y;

    using Acme::Tank::default_speed;
    using Acme::Tank::speed;
    using Acme::Tank::stop;
    using Acme::Tank::direction;
    using Acme::Tank::lives_count;

	using BaseObject = ::BaseObject;

    /**
     * @brief A structure that holds the keys corresponding to the player's tank controls.
     */
    struct PlayerKeys {
        PlayerKeys(): up(SDL_SCANCODE_UNKNOWN), down(SDL_SCANCODE_UNKNOWN), left(SDL_SCANCODE_UNKNOWN), right(SDL_SCANCODE_UNKNOWN), fire(SDL_SCANCODE_UNKNOWN) {}
        PlayerKeys(SDL_Scancode u, SDL_Scancode d, SDL_Scancode l, SDL_Scancode r, SDL_Scancode f): up(u), down(d), left(l), right(r), fire(f) {}
        /**
         * Key corresponding to driving up.
         */
        SDL_Scancode up;
        /**
         * Key corresponding to driving down.
         */
        SDL_Scancode down;
        /**
         * Key corresponding to driving left.
         */
        SDL_Scancode left;
        /**
         * Key corresponding to driving right.
         */
        SDL_Scancode right;
        /**
         * Key corresponding to projectile firing.
         */
        SDL_Scancode fire;
    };

    /**
     * Creating a player's tank
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - player type
     */
    Player(double x, double y, sprite_t type, TankStateFlag tsf = TankStateFlag::TSF_DEFAULT);

    /**
     * The function is responsible for changing the animation of the player's tank and for checking the status of pressed keys and the reaction to the keys that control the player's tank.
     * @param dt - time since the last function call, used when changing the animation
     */
    void update(Uint32 dt);
    /**
     * This function is responsible for subtracting health, clearing all flags and turning on the animation of the tank formation.
     */
    void respawn();
    /**
     * The function is responsible for turning on the tank explosion animation if the tank did not have a cover, a boat or three stars.
     */
    void destroy();
    /**
     * The function is responsible for creating a projectile if the maximum number of them has not yet been created,
     * giving it more speed if the player has at least one star and adding increased damage if the player has three stars.
     * @return pointer to the created projectile, if no projectile has been created it returns @a nullptr
     */
    Bullet* fire();

    /**
     * The function changes the number of stars you currently have. When the number of stars is non-zero, the tank's default speed is increased,
     * a for the number of stars greater than 1 and for each positive @a c the maximum number of bullets is increased.
     * @param c - change the number of stars, it can be negative
     */
    void changeStarCountBy(int c);

    /**
     * Keys controlling the current player's movements.
     */
    PlayerKeys player_keys;
};
