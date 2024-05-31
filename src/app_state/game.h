#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "iappstate.h"
#include "appconfig.h"

#ifdef A0S_SCHEMA_ICE
typedef BaseObject Object;
#endif // A0S_SCHEMA_ICE

namespace net { class NetGame; } // namespace net

/**
 * @brief The class is responsible for the movement of all tanks and interactions between tanks and between tanks and other objects on the map
 */
class Game : public IAppState {
	friend class net::NetGame;

    /**
     * Loading a level map from a file
     * @param path - path to the map file
     */
    void loadLevel(const uint8_t *data);
    /**
     * Removing remaining enemies, players, map objects and bonuses
     */
    void clearLevel();
    /**
     * Load a new level and create new players if they do not already exist.
     * @see Game::loadLevel(std::string path)
     */
    void nextLevel();
    /**
     * Creating a new enemy if the number of enemies on the board is less than 4, assuming that all 20 enemies on the map have not already been created.
     * The function generates different levels of enemy armor depending on the level; the higher the round number, the greater the chance that the opponent has armor level four.
     * The armor level number tells you how many times you need to hit the enemy with the projectile to destroy it. This number takes values from 1 to 4 and corresponds to the different colors of the tank.
     * The generated opponent has an additional chance that hitting him will result in a bonus on the board.
     */
    void generateEnemy();
    /**
     * The function generates a random bonus on the map and sets it in a position that does not interfere with the eagle.
     */
    void generateBonus();

    /**
     * Checking if the tank can move forward freely if it is not stopped. The function does not allow you to travel outside the board.
     * If the tank drives onto ice, it causes it to skid. If the tank has the "Boat" bonus, it can pass through water. Tanks cannot run over the eagle.
     * @param tank - the tank for which we check collisions
     * @param dt - last time change, assuming small changes in subsequent time steps, we can predict the next position of the tank and react accordingly.
     */
    void checkCollisionTankWithLevel(Tank* tank, Uint32 dt);
    /**
     * Checking whether there is a collision between the tested tanks, if so both are stopped.
     * @param tank1
     * @param tank2
     * @param dt
     */
    void checkCollisionTwoTanks(Tank* tank1, Tank* tank2, Uint32 dt);

    /**
     * Check whether the selected projectile does not collide with any map element (water and ice are ignored). If so, the missile and the object are destroyed.
     * If you hit heads, you lose.
     * @param bullet - bullet
     */
    void checkCollisionBulletWithLevel(Bullet* bullet);
    /**
     * Checking the collision of the projectile with bushes (bushes) on the map. The destruction of bushes and the projectile occurs when it has increased damage.
     * @param bullet - bullet
     * @see Bullet::increased_damage
     */
    void checkCollisionBulletWithBush(Bullet* bullet);
    /**
     * Checking whether a given player hit the selected opponent. If so, the player gets points and the opponent loses one level of armor.
     * @param player - player
     * @param enemy - enemy
     */
    void checkCollisionPlayerBulletsWithEnemy(Player* player, Enemy* enemy);
    /**
     * Checking whether the opponent did not hit the player with a projectile. If so, the player loses one life unless he had a cover.
     * @param enemy - enemy
     * @param player - player
     */
    void checkCollisionEnemyBulletsWithPlayer(Enemy* enemy, Player* player);
    /**
     * If two projectiles collide, both are destroyed.
     * @param bullet1
     * @param bullet2
     */
    void checkCollisionTwoBullets(Bullet* bullet1, Bullet* bullet2);
    /**
     * Checking whether the player has not taken the bonus. If so, the appropriate reaction occurs:
     * @li Grenade - visible enemies are destroyed
     * @li Helmet - the player gets temporary shielding from all projectiles
     * @li Clock - stopping visible enemies
     * @li Łopata - Create a temporary stone wall around the eagle
     * @li Tank - increase the number of player's lives by 1
     * @li Star - improvement of the player's tank (increased speed, number of bullets)
     * @li Weapon - max player upgrade
     * @li Łódź - possibility of crossing the water
     * For obtaining a bonus, the player receives additional points.
     * @paramplayer
     * @param bonus
     */
    void checkCollisionPlayerWithBonus(Player* player, Bonus* bonus);

    /**
     * Number of map grid columns.
     */
    int m_level_columns_count;
    /**
     * Number of map grid rows.
     */
    int m_level_rows_count;
    /**
     * Obstacles on the map.
     */
    std::vector< std::vector <Object*> > m_level;
    /**
     * Bushes on the map.
     */
    std::vector<Object*> m_bushes;

    /**
     * Collection of enemies.
     */
    std::vector<Enemy*> m_enemies;
protected: // tmp
    /**
     * Collection of remaining players.
     */
    std::vector<Player*> m_players;
private: // tmp
    /**
     * Collection of killed players.
     */
    std::vector<Player*> m_killed_players;
    /**
     * A collection of bonuses on the map.
     */
    std::vector<Bonus*> m_bonuses;
    /**
     * Eagle object.
     */
    Eagle* m_eagle;

    /**
     * Current level number.
     */
    int m_current_level;
    /**
     * Number of players in selected game mode 1 or 2.
     */
    int m_player_count;
    /**
     * Number of remaining enemies to kill in the level
     */
    unsigned int m_enemy_to_kill;

    /**
     * The variable stores whether the level's start screen is currently displayed.
     */
    bool m_level_start_screen;
    /**
     * The variable stores information whether the eagle is protected by a stone wall.
     */
    bool m_protect_eagle;
    /**
     * Time how long the level start screen has been displayed.
     */
    Uint32 m_level_start_time;
    /**
     * Time since the last creation of an opponent.
     */
    Uint32 m_enemy_redy_time;
    /**
     * Time elapsed since winning the map.
     */
    Uint32 m_level_end_time;
    /**
     * Time how long the eagle has been protected by the stone wall.
     */
    Uint32 m_protect_eagle_time;

    /**
     * State of defeat.
     */
    bool m_game_over;
    /**
     * Position of the string "GAME OVER" if @a m_game_over is equal to @a true.
     */
    double m_game_over_position;
    /**
     * The variable stores information whether to end the current game state and go to the results display or game menu.
     */
    bool m_finished;
    /**
     * The variable says whether pause has been enabled.
     */
    bool m_pause;
    /**
     * The position number of the newly created opponent. Changed every time an opponent is created.
     */
    unsigned int m_enemy_respown_position;

public:
    /**
     * Default builder - allows single player play
     */
    Game();
    /**
     * Constructor allowing you to specify the initial number of players. The number of players can be 1 or 2, any other value will trigger a single-player game.
     * The constructor is called in @a Menu::nextState.
     * @param players_count - number of players 1 or 2
     */
    Game(int players_count);
    /**
     * Builder accepting existing players.
     * Called in @a Score::nextState
     * @param players - container with players
     * @param previous_level - variable storing the number of the previous level
     */
    Game(std::vector<Player*> players, int previous_level);

    ~Game();
    /**
     * The function returns @a true if the player has destroyed all opponents or if the head has been hit or the player has lost all lives, i.e. the player has lost.
     * @return @a true or @a false
     */
    bool finished() const;
    /**
     * The function displays its number at the beginning of the round. During the game, the function is responsible for drawing the level (walls, stones, water, ice, bushes),
     * players, enemies, bonuses, heads, game status on the panel on the right (remaining opponents, remaining lives of players, round number).
     * After a loss or during a pause, displays appropriate information in the center of the screen.
     */
    void draw();
    /**
     * The function updates the status of all objects on the board (tanks, bonuses, obstacles). It also checks collisions between tanks, between tanks and level elements, and between missiles and tanks and map elements.
     * This will include removing destroyed objects, adding new enemy tanks and checking the conditions for ending the round.
     * @param dt - time since the last function call in milliseconds
     */
    void update(Uint32 dt);
    /**
     * Keystroke response occurs here:
     * @li Enter - game pause
     * @li Esc - return to menu
     * @li N - advance to the next round if the game is not lost
     * @li B - move to the previous round if the game is not lost
     * @li T - showing paths to enemy tank targets
     * @param ev - pointer to the SDL_Event union storing the type and parameters of various events, including keyboard events
     */
    void eventProcess(SDL_Event* ev);
    /**
     * Move to the next state.
     * @return pointer to @a Scores objects if the player passed or lost the round. If the player presses Esc, the function returns a pointer to the @a Menu object.
     */
    IAppState* nextState();
};
