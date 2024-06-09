// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/commander.h"
namespace net::tx {
boost::asio::awaitable<Commander::Command> Commander::readCommand_(Base::tcp::socket &socket, commandsBuffer_t const& commandsBuffer) {
	command_t commandRaw;
	if ( !co_await async_read_( socket, &commandRaw ) )
		co_return Command::undefined;
	auto command = static_cast< Command >( commandRaw );
	answerSize_t answerSize = 0;
	if ( auto it = commandsBuffer.find( command ); it != commandsBuffer.end( ) ) 
		answerSize = it ->second.size( );
	if ( !co_await async_write_( socket, &answerSize ) )
		co_return Command::undefined;
	co_return command;
}
boost::asio::awaitable<bool> Commander::writeCommand_(Base::tcp::socket &socket, Command command, answerSize_t *answerSize) {
	const auto commandRaw = static_cast< command_t >( command );
	if ( !co_await async_write_( socket, &commandRaw ) )
		co_return false;
	if ( !co_await async_read_( socket, answerSize ) )
		co_return false;
	co_return true;
}
} // namespace net::tx
