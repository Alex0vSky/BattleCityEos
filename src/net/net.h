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
	template <class C>
	struct TypeIdentifier {
		constexpr static int _id{ };
		constexpr static auto id() {
			return &_id;
		}
	};
	static constexpr auto c_idBrick = TypeIdentifier< Brick >::id( );
	static constexpr auto c_idObject = TypeIdentifier< Object >::id( );

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count);

	void draw() override;

	// default-constructed variant holds a value of its first alternative: nullptr_t
	using element_t = std::variant< nullptr_t, Object, Brick >;

private:
	template<typename T> using container_t = cista::offset::vector< T >;
	using level_t = container_t< container_t< element_t > >;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_playerPtr;
	tx::Exchanger m_tx;
	level_t m_level;

	template <typename... Args>
	static constexpr auto serialize(Args&&... args) {
		return cista::serialize< c_MODE >( std::forward< Args >( args )... );
	}
	template <typename T>
	static constexpr auto deserialize(cista::byte_buf const& buffer) {
		return cista::deserialize< T, c_MODE >( buffer);
	}

	using func_t = std::function< void(int i, int j, Object *&object) >;
	void forEachLevel(func_t cb) {
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
	void update(Uint32 dt) override;
};
} // namespace net
