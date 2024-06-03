// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/exchanger.h"
namespace net::tx {
boost::asio::awaitable<bool> Exchanger::clientSide(Commander::Command command, unit_t *buffer) {
	buffer ->clear( );
	tcp::socket socket( co_await boost::asio::this_coro::executor );
	auto [error1] = co_await socket.async_connect( c_endpointClient, c_tuple );
	if ( error1 ) 
		co_return false;
	//printf( "[Exchanger::clientSide] connected...\n" ); //
	if ( !co_await Commander::writeCommand_( socket, command ) )
		co_return false;
	while ( true ) {
		std::uint8_t data[ 1024 ];
		auto [error2, n] = co_await socket.async_read_some( boost::asio::buffer( data ), Base::c_tuple );
		if ( n ) 
			std::copy( data, data + n, std::back_inserter( *buffer ) );
		if ( boost::asio::error::eof == error2 ) 
			break;
		if ( error2 ) 
			co_return false;
	}
	//printf( "[Exchanger::clientSide] read: %d\n", buffer ->size( ) ); //
	co_return true;
}

boost::asio::awaitable<void> Exchanger::Holder::finish() {
	//printf( "[Exchanger::serverSide] acceptor...\n" ); //
	while ( true ) {
		auto [error1, socket] = co_await m_acceptorPtr ->async_accept( c_tuple );
		if ( boost::asio::error::operation_aborted == error1 ) // due `m_acceptorPtr ->cancel( )`
			break;
		if ( !socket.is_open( ) || error1 )
			continue;
		auto it = m_commandsBuffer.find( co_await readCommand_( socket ) );
		if ( it == m_commandsBuffer.end( ) )
			continue;
		cista::byte_buf buffer = it ->second;
		auto [error2, nwritten] = co_await boost::asio::async_write( socket, boost::asio::buffer( buffer ), Base::c_tuple );
		if ( buffer.size( ) != nwritten ) 
			continue;
		//printf( "[Exchanger::serverSide] sent: %d\n", nwritten ); //
	}
}
} // namespace net::tx
