#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include <boost/asio.hpp>
#include <boost/config/user.hpp>

namespace net {
/**
 * Wrapping boost::asio
 */
class Tx {
public:
	using awaitable = boost::asio::awaitable<void>;
	using tcp = boost::asio::ip::tcp;
	using address_v4 = boost::asio::ip::address_v4;

	static constexpr u_short c_port = 55555;
	static constexpr address_v4::bytes_type c_host{ 127, 0, 0, 1 };
	std::unique_ptr< boost::asio::io_context > m_ioContext;

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
	static constexpr auto c_detached = boost::asio::detached;

	template <typename F>
	inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE( decltype( c_detached ),
		typename detail::awaitable_signature<typename result_of<F()>::type>::type)
	co_spawn_(F&& f) {
		return co_spawn( m_ioContext ->get_executor( ), std::forward<F>(f), c_detached );
	}

	using command_t = uint32_t;
	enum class Command : command_t { undefined
		, GetFullMap
		, ChangeMapElement
		, Something
	};

	static boost::asio::awaitable<bool> readCommand_(tcp::socket &socket, Command *command) {
		*command = Command::undefined;
		command_t commandRaw;
		const size_t commandSizeof = sizeof( commandRaw );
		auto [error, n] = co_await socket.async_read_some( boost::asio::buffer( &commandRaw, commandSizeof ), c_tuple );
		if ( n != commandSizeof || error )
			co_return false;
		*command = static_cast< Command >( commandRaw );
		co_return true;
	}
	static boost::asio::awaitable<Command> readCommand_(tcp::socket &socket) {
		Command command = Command::undefined;
		command_t commandRaw;
		const size_t commandSizeof = sizeof( commandRaw );
		auto [error, n] = co_await socket.async_read_some( boost::asio::buffer( &commandRaw, commandSizeof ), c_tuple );
		if ( n == commandSizeof && !error )
			command = static_cast< Command >( commandRaw );
		co_return command;
	}
	static boost::asio::awaitable<bool> writeCommand_(tcp::socket &socket, Command command) {
		const auto commandRaw = static_cast< command_t >( command );
		const size_t commandSizeof = sizeof( commandRaw );
		auto [error, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( &commandRaw, commandSizeof ), c_tuple );
		co_return ( nwritten == commandSizeof && !error );
	}

public:
    /**
     * Create network transmission
     */
	Tx();
	~Tx();

    /**
     * poc
     */
	using funct_t = std::function< awaitable ( boost::asio::io_context *) >;
	void update(funct_t f1, funct_t f2);

};
} // namespace net
