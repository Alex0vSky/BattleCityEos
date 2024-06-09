// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/exchanger.h"
namespace net::tx {
boost::asio::awaitable<bool> Exchanger::clientSide(Commander::Command command, unit_t *buffer) {
	buffer ->clear( );
	//printf( "[Exchanger::clientSide] connected...\n" ); //
	Commander::answerSize_t answerSize = 0;
	if ( !co_await Commander::writeCommand_( m_socketClient, command, &answerSize ) )
		co_return false;
	while ( true ) {
		std::uint8_t data[ 1024 ];
		auto [error2, n2] = co_await m_socketClient.async_read_some( boost::asio::buffer( data ), Base::c_tuple );
		if ( n2 ) 
			std::copy( data, data + n2, std::back_inserter( *buffer ) );
		if ( buffer ->size( ) == answerSize ) 
			break;
		if ( error2 ) 
			co_return false;
	}
	//printf( "[Exchanger::clientSide] read: %d\n", buffer ->size( ) ); //
	co_return !buffer ->empty( );
	//co_return true;
}

// TODO(alex): process not more then XXX time
boost::asio::awaitable<void> Exchanger::Holder::finish() {
	//printf( "[Exchanger::serverSide] acceptor...\n" ); //
	while ( !m_commandsBuffer.empty( ) ) {
		auto command = co_await readCommand_( *m_socketPtr, m_commandsBuffer );
		auto it = m_commandsBuffer.find( command );
		if ( it == m_commandsBuffer.end( ) )
			break;
		cista::byte_buf buffer = it ->second;
		m_commandsBuffer.erase( it );
		auto [error2, nwritten] = co_await boost::asio::async_write( *m_socketPtr, boost::asio::buffer( buffer ), Base::c_tuple );
		if ( buffer.size( ) != nwritten ) 
			break;
		//printf( "[Exchanger::serverSide] sent: %d\n", nwritten ); //
	}
}
} // namespace net::tx
