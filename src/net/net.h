#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "iappstate.h"
#include "appconfig.h"
#include "game.h"

namespace net {
class NetPlayer : public Player {
	using Player::Player;

public:
	void update(Uint32 dt) override;
};

class NetGame : public ::Game {
	void update(Uint32 dt) override;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_player;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count) :
		// tmp
		Game( 1 )
	{}
};
} // namespace net
