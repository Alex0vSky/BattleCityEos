#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "iappstate.h"
#include "appconfig.h"
#include "game.h"
#include "net/tx/eventer.h"

namespace net {
namespace tx { class DataExchanger; class EventExchanger; } // namespace tx 
class NetGame : public ::Game {
	// TODO(alex): get from network
	static constexpr auto c_MODE = cista::mode::NONE
			| cista::mode::WITH_VERSION
			| cista::mode::WITH_INTEGRITY
			| cista::mode::DEEP_CHECK
		;
	template<typename T> using container_t = cista::offset::vector< T >;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count);
	~NetGame();

	void draw() override;
	void update(Uint32 dt) override;

	// default-constructed variant holds a value of its first alternative: nullptr_t
	using element_t = std::variant< nullptr_t, Object, Brick >;
	using Level = container_t< container_t< element_t > >;

private:
	virtual void generateEnemy() override;
	bool m_fullMap = false;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_playerPtr;

	using EventData = tx::Eventer::EventData;
	using EventName = tx::Eventer::EventName;
	std::unique_ptr< tx::DataExchanger > m_txEmmiter;
	std::unique_ptr< tx::EventExchanger > m_txEventer;
	Level m_level;

	template <typename... Args>
	static constexpr auto serialize_(Args&&... args) {
		return cista::serialize< c_MODE >( std::forward< Args >( args )... );
	}
	template <typename T>
	static constexpr auto deserialize_(cista::byte_buf const& data) {
		return cista::deserialize< T, c_MODE >( data );
	}

	using func_t = std::function< void(int i, int j, Object *&object) >;
	void forEachParentLevel_(func_t cb) {
		std::for_each( Game::m_level.begin( ), Game::m_level.end( ), [this, cb](std::vector<Object *> &element) {
				int i = &element - &Game::m_level[ 0 ];
				int j = -1;
				for ( Object *&object : element ) {
					++j;
					//if ( !object ) 
					//	continue;
					cb( i, j, object );
				}
			} );
	}
};

class NetPlayer : public Player {
	using Player::Player;

public:
	using Tank::m_flags;
	using Object::m_current_frame;
	bool m_isDurty = true;

	void update(Uint32 dt) override;
	void shot();

	// or `std::list` to easy pop_back
	using shoots_t = cista::offset::vector< Bullet >;
	shoots_t getShots();
	bool getBulletOfShot(Bullet *bullet);

private:
public: // tmp
	shoots_t m_shots;

public:
	auto cista_members();
};
} // namespace net
