#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "iappstate.h"
#include "appconfig.h"
#include "game.h"
#include "net/tx/exchanger.h"

namespace net {
class NetPlayer : public Player {
	using Player::Player;

public:
	void update(Uint32 dt) override;
};

class NetGame : public ::Game {
	// TODO(alex): get from network
	static constexpr auto c_MODE = cista::mode::NONE
			| cista::mode::WITH_VERSION
			| cista::mode::WITH_INTEGRITY
			| cista::mode::DEEP_CHECK
		;

	tx::Exchanger m_tx;

	void update(Uint32 dt) override;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_playerPtr;
	template<typename T> using store_t = cista::offset::vector< T >;
	using level_t = store_t< store_t< Object > >;
	level_t m_level;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count);

	void draw() override;
};
} // namespace net
