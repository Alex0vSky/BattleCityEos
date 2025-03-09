#include "type.h"
#include "engine\SpriteConfig.h"
SpriteConfig::SpriteConfig() :
	m_configs( {	
			{ sprite_t::ST_TANK_A, { 128, 0, 32, 32, 2, 100, true, sprite_t::ST_TANK_A } }
			, { sprite_t::ST_TANK_B, { 128, 64, 32, 32, 2, 100, true, sprite_t::ST_TANK_B } }
			, { sprite_t::ST_TANK_C, { 128, 128, 32, 32, 2, 100, true, sprite_t::ST_TANK_C } }
			, { sprite_t::ST_TANK_D, { 128, 192, 32, 32, 2, 100, true, sprite_t::ST_TANK_D } }
			, { sprite_t::ST_PLAYER_1, { 640, 0, 32, 32, 2, 50, true, sprite_t::ST_PLAYER_1 } }
			, { sprite_t::ST_PLAYER_2, { 768, 0, 32, 32, 2, 50, true, sprite_t::ST_PLAYER_2 } }
			, { sprite_t::ST_BRICK_WALL, { 928, 0, 16, 16, 1, 200, false, sprite_t::ST_BRICK_WALL } }
			, { sprite_t::ST_STONE_WALL, { 928, 144, 16, 16, 1, 200, false, sprite_t::ST_STONE_WALL } }
			, { sprite_t::ST_WATER, { 928, 160, 16, 16, 2, 350, true, sprite_t::ST_WATER } }
			, { sprite_t::ST_BUSH, { 928, 192, 16, 16, 1, 200, false, sprite_t::ST_BUSH } }
			, { sprite_t::ST_ICE, { 928, 208, 16, 16, 1, 200, false, sprite_t::ST_ICE } }
			, { sprite_t::ST_BONUS_GRENADE, { 896, 0, 32, 32, 1, 200, false, sprite_t::ST_BONUS_GRENADE } }
			, { sprite_t::ST_BONUS_HELMET, { 896, 32, 32, 32, 1, 200, false, sprite_t::ST_BONUS_HELMET } }
			, { sprite_t::ST_BONUS_CLOCK, { 896, 64, 32, 32, 1, 200, false, sprite_t::ST_BONUS_CLOCK } }
			, { sprite_t::ST_BONUS_SHOVEL, { 896, 96, 32, 32, 1, 200, false, sprite_t::ST_BONUS_SHOVEL } }
			, { sprite_t::ST_BONUS_TANK, { 896, 128, 32, 32, 1, 200, false, sprite_t::ST_BONUS_TANK } }
			, { sprite_t::ST_BONUS_STAR, { 896, 160, 32, 32, 1, 200, false, sprite_t::ST_BONUS_STAR } }
			, { sprite_t::ST_BONUS_GUN, { 896, 192, 32, 32, 1, 200, false, sprite_t::ST_BONUS_GUN } }
			, { sprite_t::ST_BONUS_BOAT, { 896, 224, 32, 32, 1, 200, false, sprite_t::ST_BONUS_BOAT } }
			, { sprite_t::ST_SHIELD, { 976, 0, 32, 32, 2, 45, true, sprite_t::ST_SHIELD } }
			, { sprite_t::ST_CREATE, { 1008, 0, 32, 32, 10, 100, false, sprite_t::ST_CREATE } }
			, { sprite_t::ST_DESTROY_TANK, { 1040, 0, 64, 64, 7, 70, false, sprite_t::ST_DESTROY_TANK } }
			, { sprite_t::ST_DESTROY_BULLET, { 1108, 0, 32, 32, 5, 40, false, sprite_t::ST_DESTROY_BULLET } }
			, { sprite_t::ST_BOAT_P1, { 944, 96, 32, 32, 1, 200, false, sprite_t::ST_BOAT_P1 } }
			, { sprite_t::ST_BOAT_P2, { 976, 96, 32, 32, 1, 200, false, sprite_t::ST_BOAT_P2 } }
			, { sprite_t::ST_EAGLE, { 944, 0, 32, 32, 1, 200, false, sprite_t::ST_EAGLE } }
			, { sprite_t::ST_DESTROY_EAGLE, { 1040, 0, 64, 64, 7, 100, false, sprite_t::ST_DESTROY_EAGLE } }
			, { sprite_t::ST_FLAG, { 944, 32, 32, 32, 1, 200, false, sprite_t::ST_FLAG } }
			, { sprite_t::ST_BULLET, { 944, 128, 8, 8, 1, 200, false, sprite_t::ST_BULLET } }
			, { sprite_t::ST_LEFT_ENEMY, { 944, 144, 16, 16, 1, 200, false, sprite_t::ST_LEFT_ENEMY } }
			, { sprite_t::ST_STAGE_STATUS, { 976, 64, 32, 32, 1, 200, false, sprite_t::ST_STAGE_STATUS } }
			, { sprite_t::ST_TANKS_LOGO, { 0, 260, 406, 72, 1, 200, false, sprite_t::ST_TANKS_LOGO } }
		
		} )
{}
