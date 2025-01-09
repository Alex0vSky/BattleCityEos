#pragma once // src\schema\vanilla\objects\player.h // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "tank.h"

/**
 * @brief Class corresponding to player tanks.
 */
class Player : public Tank {
    /**
     * Current number of stars; may be in the range [0, 3].
     */
    int star_count = 0;
    /**
     * The time that has passed since the last missile shot.
     */
    Uint32 m_fire_time = 0;
    /**
     * Machine is in movement.
     */
    bool m_movement = false;
    /**
     * It is menu tank.
     */
    bool m_menu = false;

public:
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
     * Create a player in the first player position.
     * @see AppConfig::player_starting_point
     */
    Player();
    /**
     * Creating a player's tank
     * @param x - horizontal starting position
     * @param y - vertical starting position
     * @param type - player type
     */
    Player(double x, double y, SpriteType type, TankStateFlag tsf = TankStateFlag::TSF_DEFAULT);

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
    /**
     * The player's current points.
     */
    unsigned score;
};
