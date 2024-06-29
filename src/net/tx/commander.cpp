// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/commander.h"
namespace net::tx {
static bool myYield(boost::asio::any_io_executor const& executor) {
	////m_ioContextPtr ->yield( );
	////m_ioContextPtr ->post( yield );
	////m_ioContextPtr ->post( boost::asio::get_associated_executor(yield), yield );
	//m_ioContextPtr ->poll_one( );
	////executor.context( ).
	////boost::asio::get_associated_executor( executor ).context( ).get_executor( ).;
	boost::asio::io_context &ioContext = executor.target< boost::asio::io_context::executor_type >( )->context( );
	ioContext.poll_one( );
	return true;
}
boost::asio::awaitable<Commander::Command> Commander::readCommand_(tcp::socket &socket, commandsBuffer_t const& commandsBuffer) {
	command_t commandRaw;
	if ( !co_await async_read_( socket, &commandRaw ) )
		co_return Command::undefined;
	auto command = static_cast< Command >( commandRaw );

	answerSize_t answerSize = 0;
	auto it = commandsBuffer.end( );
	unsigned i = 0;
	do {
		it = commandsBuffer.find( command );
		if ( ++i > 1 )
			__nop( );
	} while( commandsBuffer.end( ) == it && myYield( co_await boost::asio::this_coro::executor ) );
	answerSize = it ->second.size( );
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
