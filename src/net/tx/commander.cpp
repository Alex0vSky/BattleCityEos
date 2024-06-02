// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/commander.h"

namespace net::tx {
boost::asio::awaitable<Commander::Command> Commander::readCommand_(Base::tcp::socket &socket) {
	command_t commandRaw;
	auto [error, n] = co_await socket.async_read_some( boost::asio::buffer( &commandRaw, c_sizeof ), Base::c_tuple );
	if ( n == c_sizeof && !error )
		co_return static_cast< Command >( commandRaw );
	co_return Command::undefined;
}
boost::asio::awaitable<bool> Commander::writeCommand_(Base::tcp::socket &socket, Command command) {
	const auto commandRaw = static_cast< command_t >( command );
	auto [error, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( &commandRaw, c_sizeof ), Base::c_tuple );
	co_return ( nwritten == c_sizeof && !error );
}
} // namespace net::tx
