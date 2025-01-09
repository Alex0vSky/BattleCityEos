// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/eventer.h"
namespace net::tx {
AwaitableBool Eventer::writeEvent_(Socket &socket, EventName eventName, Buffer const& eventData) {
	const auto eventNameRaw = static_cast< TypeEvent >( eventName );
	//printf( "[Eventer::writeEvent_] eventNameRaw: %d\n", eventNameRaw ); //
	if ( !co_await async_write_( socket, eventNameRaw ) )
		co_return false;
	const TypeSizeEventData sizeEventData = eventData.size( );
	if ( !co_await async_write_( socket, sizeEventData ) )
		co_return false;
	if ( !co_await async_write_( socket, eventData ) )
		co_return false;
	//printf( "[Eventer::writeEvent_] wait pong...\n" ); //
	TypePong pong;
	if ( !co_await async_read_( socket, &pong ) )
		// TODO(alex): increase reliability and information content
		co_return false;
	co_return c_pongSuccess == pong;
}
AwaitableBool Eventer::readEvent_(Socket &socket, EventName *event, Buffer *eventData) {
	TypeEvent eventNameRaw;
	if ( !co_await async_read_( socket, &eventNameRaw ) )
		co_return false;
	//printf( "[Eventer::readEvent_] eventNameRaw: %d\n", eventNameRaw ); //
	*event = static_cast< EventName >( eventNameRaw );
	if ( !Valid::isValue( *event ) ) {
		printf( "[Eventer::readEvent_] async write pongWrong\n" );
		co_await async_write_( socket, c_pongWrong );
		co_return *event = EventName::invalid, false;
	}
	TypeSizeEventData sizeEventData = 0;
	if ( !co_await async_read_( socket, &sizeEventData ) )
		co_return *event = EventName::undefined, false;
	if ( !co_await async_read_( socket, eventData, sizeEventData ) )
		co_return *event = EventName::undefined, false;
	if ( !co_await async_write_( socket, c_pongSuccess ) )
		co_return *event = EventName::undefined, false;
	co_return true;
}
} // namespace net::tx
