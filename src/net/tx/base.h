#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include <boost/asio.hpp>
#include <boost/config/user.hpp>

namespace net::tx {
class Exchanger;
/**
 * Wrapping boost::asio
 */
class Base {
	static constexpr u_short c_port = 55555;
	static constexpr boost::asio::ip::address_v4::bytes_type c_host{ 127, 0, 0, 1 };

	template <typename... Args>
	static constexpr auto as_tuple(Args&&... args) {
		return boost::asio::experimental::as_tuple( std::forward< Args >( args )... );
	}

public:
	using function_t = std::function< boost::asio::awaitable< void > (Exchanger *) >;
	using awaitable = boost::asio::awaitable< void >;
	using tcp = boost::asio::ip::tcp;
    /**
     * Call client and server simultaneously
     */
	void update(function_t client, function_t server);

protected:
    /**
     * Create network transmission
     */
	Base();

	boost::asio::io_context m_ioContext;
	const tcp::endpoint c_endpointClient, c_endpointServer{ tcp::v4( ), c_port };
	tcp::acceptor m_acceptor;
	static constexpr auto c_detached = boost::asio::detached;
	static constexpr auto c_tuple = as_tuple( boost::asio::use_awaitable_t{ } );

	template <typename F>
	inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE( decltype( c_detached ),
		typename detail::awaitable_signature<typename result_of<F()>::type>::type)
	co_spawn_(F&& f) {
		return co_spawn( m_ioContext.get_executor( ), std::forward<F>(f), c_detached );
	}
};
} // namespace net::tx
