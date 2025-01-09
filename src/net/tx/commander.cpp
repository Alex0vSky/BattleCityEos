// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/commander.h"
namespace net::tx {
AwaitableBool Commander::readCommand_(Socket &socket, Command *command) {
	TypeCommand commandRaw;
	if ( !co_await async_read_( socket, &commandRaw ) )
		co_return *command = Command::undefined_, false;
	*command = static_cast< Command >( commandRaw );
	if ( !Valid::isValue( commandRaw ) ) {
		co_await async_write_( socket, Response::InvalidCommand );
		co_return *command = Command::invalid_, false;
	}
	if ( !co_await async_write_( socket, Response::Success ) )
		co_return *command = Command::undefined_, false;
	co_return true;
}
AwaitableBool Commander::writeData_(Socket &socket, Buffer const& data) {
	co_return true
			&& co_await async_write_( socket, data.size( ) )
			&& co_await async_write_( socket, data )
		;
}
AwaitableBool Commander::writeCommand_(Socket &socket, Command command, answerSize_t *answerSize) {
	const auto commandRaw = static_cast< TypeCommand >( command );
	if ( !co_await async_write_( socket, commandRaw ) )
		co_return false;
	Response response = Response::undefined_;
	if ( !co_await async_read_( socket, &response ) )
		co_return false;
	if ( Response::Success != response )
		co_return false;
	if ( !co_await async_read_( socket, answerSize ) )
		co_return false;
	co_return true;
}
} // namespace net::tx
