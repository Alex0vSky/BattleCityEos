#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "objects/player.h"
/**
 * @brief A class containing a set of application parameters.
 */
struct AppConfig {
     /**
      * The path to the texture of objects.
      */
     static constexpr std::string_view texture_path = "resources/png/texture.png";
     /**
      * Path to the levels directory.
      */
     static constexpr std::string_view levels_path = "resources/level/";
     /**
      * Path to the font.
      */
     static constexpr std::string_view font_name = "resources/font/prstartk.ttf";
     /**
      * Path to the sounds directory.
      */
     static constexpr std::string_view sounds_path = "resources/sound/";
     /**
      *Text displayed after a loss.
      */
     static constexpr std::string_view game_over_text = "GAME OVER";
     /**
      * Dimensions of the game board.
      */
     static constexpr SDL_Rect map_rect{0, 0, 26*16, 26*16};
     /**
      * Dimensions and location of the game status area relative to the board.
      */
     static constexpr SDL_Rect status_rect{26*16, 0, 3*16, AppConfig::map_rect.h};
     /**
      * Application window size.
      */
     inline static SDL_Rect windows_rect{0, 0, AppConfig::map_rect.w + AppConfig::status_rect.w, AppConfig::map_rect.h};
     /**
      * The size of the cell on the board.
      */
     static constexpr SDL_Rect tile_rect{0, 0, 16, 16};
     /**
      * Two starting player positions.
      */
     const inline static std::vector<SDL_Point> player_starting_point{ {128, 384}, {256, 384} };
     /**
      * Three enemy starting positions.
      */
     const inline static std::vector<SDL_Point> enemy_starting_point{ {1, 1}, {192, 1}, {384, 1} };
     /**
      * Controlling players tanks.
      */
     const inline static std::vector<Player::PlayerKeys> player_keys{
			{SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SDL_SCANCODE_LALT }
			, {SDL_SCANCODE_W, SDL_SCANCODE_S, SDL_SCANCODE_A, SDL_SCANCODE_D, SDL_SCANCODE_RALT }
		};
     /**
      * Display time of the round number at the start of the round.
      */
     const static unsigned level_start_time = 2000;
     /**
      * Duration of slipping on ice in milliseconds.
      */
     const static unsigned slip_time = 380;
     /**
      * Number of enemies to kill in one round.
      */
     const static unsigned enemy_start_count = 20;
     /**
      * The time after which a new enemy can appear on the map in milliseconds.
      */
     const static unsigned enemy_redy_time = 500;
     /**
      * Default maximum number of bullets a player can fire.
      */
     const static unsigned player_bullet_max_size = 2;
     /**
      * Time to show results after countdown ends in milliseconds.
      */
     const static unsigned score_show_time = 3000;
     /**
      * The time during which the bonus is visible on the map in milliseconds.
      */
     const static unsigned bonus_show_time = 10000;
     /**
      * Cover operation time in milliseconds.
      */
     const static unsigned tank_shield_time = 10000;
     /**
      * The length of time that enemies are frozen in milliseconds.
      */
     const static unsigned tank_frozen_time = 8000;
     /**
      * Time between killing all enemies and going to the results window in milliseconds.
      */
     const static unsigned level_end_time = 5000;
     /**
      * Duration of the stone shield around the eagle in milliseconds.
      */
     const static unsigned protect_eagle_time = 15000;
     /**
      * Bonus flashing time in milliseconds.
      */
     const static unsigned bonus_blink_time = 350;
     /**
      * Minimum time between player firing bullets in milliseconds.
      */
     const static unsigned player_reload_time = 120;
     /**
      * Maximum number of tanks on the map at one time.
      */
     const static unsigned int enemy_max_count_on_map = 4;
     /**
      * The speed of the "GAME OVER" button.
      */
     const inline static double game_over_entry_speed = 0.13;
     /**
      * Nominal speed of the tank.
      */
     const inline static double tank_default_speed = 0.08;
     /**
      * Nominal bullet speed.
      */
     const inline static double bullet_default_speed = 0.23;
     /**
      * The variable stores information about whether showing opponents goals has been enabled.
      */
     inline static bool show_enemy_target = false;
};
#include "engine/renderer.h"
#include "engine/engine.h"
