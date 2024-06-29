#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "iappstate.h"
#include "appconfig.h"
#include "game.h"
#include "net/tx/exchanger.h"
#include "net/tx/EventExchanger.h"

namespace net {
class NetGame : public ::Game {
	// TODO(alex): get from network
	static constexpr auto c_MODE = cista::mode::NONE
			| cista::mode::WITH_VERSION
			| cista::mode::WITH_INTEGRITY
			| cista::mode::DEEP_CHECK
		;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count, bool isServer);
	~NetGame();

	void draw() override;
	void update(Uint32 dt) override;

	// default-constructed variant holds a value of its first alternative: nullptr_t
	using element_t = std::variant< nullptr_t, Object, Brick >;

private:
	template<typename T> using container_t = cista::offset::vector< T >;
	using level_t = container_t< container_t< element_t > >;

	bool m_isServer;
	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_playerPtr;
	using EventData = tx::Eventer::EventData;
	using EventName = tx::Eventer::EventName;
	using EventShootOwner = tx::EventExchanger::EventData::Shoot::Owner;
	tx::exchanger m_txEmmiter;
	tx::EventExchanger m_txEventer;
	level_t m_level;

	template <typename... Args>
	static constexpr auto serialize_(Args&&... args) {
		return cista::serialize< c_MODE >( std::forward< Args >( args )... );
	}
	template <typename T>
	static constexpr auto deserialize_(cista::byte_buf const& buffer) {
		return cista::deserialize< T, c_MODE >( buffer);
	}

	using func_t = std::function< void(int i, int j, Object *&object) >;
	void forEachLevel_(func_t cb) {
		std::for_each( Game::m_level.begin( ), Game::m_level.end( ), [this, cb](std::vector<Object *> &element) {
				int i = &element - &Game::m_level[ 0 ];
				int j = -1;
				for ( Object *&object : element ) {
					++j;
					if ( !object ) 
						continue;
					cb( i, j, object );
				}
			} );
	}
};
class NetPlayer : public Player {
	using Player::Player;

public:
	void update(Uint32 dt) override;
	void shoot();

	using shoots_t = std::queue< Bullet >;
	shoots_t getShoots();

private:
	shoots_t m_shoots;
};
} // namespace net
