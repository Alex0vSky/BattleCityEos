// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/commander.h"

namespace net::tx {
boost::asio::awaitable<Commander::Command> Commander::readCommand_(Base::tcp::socket &socket, commandsBuffer_t const& commandsBuffer) {
	command_t commandRaw;
	auto [error1, n] = co_await socket.async_read_some( boost::asio::buffer( &commandRaw, c_sizeofCommand ), Base::c_tuple );
	if ( n != c_sizeofCommand || error1 )
		co_return Command::undefined;
	auto command = static_cast< Command >( commandRaw );
	answerSize_t answerSize = 0;
	if ( auto it = commandsBuffer.find( command ); it != commandsBuffer.end( ) ) 
		answerSize = it ->second.size( );
	auto [error2, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( &answerSize, c_sizeofAnswer ), Base::c_tuple );
	if ( nwritten != c_sizeofAnswer || error2 )
		co_return Command::undefined;
	co_return command;
}
boost::asio::awaitable<bool> Commander::writeCommand_(Base::tcp::socket &socket, Command command, answerSize_t *answerSize) {
	const auto commandRaw = static_cast< command_t >( command );
	auto [error1, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( &commandRaw, c_sizeofCommand ), Base::c_tuple );
	if ( nwritten != c_sizeofCommand || error1 )
		co_return false;
	auto [error2, n] = co_await socket.async_read_some( boost::asio::buffer( answerSize, c_sizeofAnswer ), Base::c_tuple );
	if ( n != c_sizeofAnswer || error2 )
		co_return false;
	co_return true;
}
} // namespace net::tx
