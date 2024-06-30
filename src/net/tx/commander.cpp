// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/commander.h"
namespace net::tx {
static bool myYield(boost::asio::any_io_executor const& executor) {
	boost::asio::io_context &ioContext = executor.target< boost::asio::io_context::executor_type >( )->context( );
	ioContext.poll_one( );
	return true;
}
boost::asio::awaitable<Commander::Command> Commander::readCommand_(tcp::socket &socket, commandsBuffer_t const& commands) {
	command_t commandRaw;
	if ( !co_await async_read_( socket, &commandRaw ) )
		co_return Command::undefined;
	auto command = static_cast< Command >( commandRaw );
	auto commands_ = commands; // tmp
	auto it = commands.end( );
	// waiting
	do it = commands.find( command );
	while ( commands.end( ) == it && myYield( co_await boost::asio::this_coro::executor ) );

	answerSize_t answerSize = it ->second.size( );
	if ( !co_await async_write_( socket, &answerSize ) )
		co_return Command::undefined;
	co_return command;
}
boost::asio::awaitable<bool> Commander::writeCommand_(tcp::socket &socket, Command command, answerSize_t *answerSize) {
	const auto commandRaw = static_cast< command_t >( command );
	if ( !co_await async_write_( socket, &commandRaw ) )
		co_return false;
	if ( !co_await async_read_( socket, answerSize ) )
		co_return false;
	co_return true;
}
} // namespace net::tx
