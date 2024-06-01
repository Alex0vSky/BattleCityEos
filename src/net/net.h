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
	using awaitable = boost::asio::awaitable<void>;
	using tcp = boost::asio::ip::tcp;
	using address_v4 = boost::asio::ip::address_v4;
	// TODO(alex): get from network
	static constexpr auto c_MODE = cista::mode::NONE
			| cista::mode::WITH_VERSION
			| cista::mode::WITH_INTEGRITY
			| cista::mode::DEEP_CHECK
		;
	static constexpr u_short c_port = 55555;
	static constexpr address_v4::bytes_type c_host{ 127, 0, 0, 1 };

	// aliases
	template <typename... Args>
	static constexpr auto as_tuple(Args&&... args) {
		return boost::asio::experimental::as_tuple( std::forward< Args >( args )... );
	}
	template <typename... Args>
	static constexpr auto as_single(Args&&... args) {
		return boost::asio::experimental::as_single( std::forward< Args >( args )... );
	}
	static constexpr auto c_tuple = as_tuple( boost::asio::use_awaitable_t{ } );
	static constexpr auto c_single = as_single( boost::asio::use_awaitable_t{ } );
	static constexpr auto c_detached = boost::asio::detached;

	template <typename F>
	inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE( decltype( c_detached ),
		typename detail::awaitable_signature<typename result_of<F()>::type>::type)
	co_spawn_(F&& f) {
		return co_spawn( m_ioContext ->get_executor( ), std::forward<F>(f), c_detached );
	}

	void update(Uint32 dt) override;

	// TODO(alex): uglyAndFast, omitt `static`, delete in App::run
	inline static std::shared_ptr< NetPlayer > m_player;

	using command_t = uint32_t;
	enum class Command : command_t { undefined
		, GetFullMap
		, ChangeMapElement
		, Something
	};
	std::unique_ptr< boost::asio::io_context > m_ioContext;

public:
    /**
     * Allows multi-player
     */
	NetGame(int players_count);

	void draw() override;
};
} // namespace net
