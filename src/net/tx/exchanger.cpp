// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/exchanger.h"
namespace net::tx {
Base::awaitableBool exchanger::clientSide(Commander::Command command, unit_t *answer) {
	Commander::answerSize_t answerSize = 0;
	if ( !co_await Commander::writeCommand_( *m_socketClient, command, &answerSize ) ) {
		printf( "[exchanger::clientSide] fail writeCommand_\n" ); //
		co_return false;
	}
	if ( !co_await async_read_( *m_socketClient, answer, answerSize ) ) {
		printf( "[exchanger::clientSide] fail async_read_\n" ); //
		co_return false;
	}
	printf( "[exchanger::clientSide] read: %d/%d\n", answerSize, answer ->size( ) ); //
	co_return !answer ->empty( );
}
Base::awaitable exchanger::Holder::finish() {
	while ( !m_commandsBuffer.empty( ) ) {
		auto command = co_await readCommand_( *m_socketPtr, m_commandsBuffer );
		if ( Commander::Command::Something == command )
			printf( "[exchanger::Holder::finish] command Something\n" ); //
		auto it = m_commandsBuffer.find( command );
		if ( it == m_commandsBuffer.end( ) ) {
			printf( "[exchanger::Holder::finish] fail m_commandsBuffer.find\n" ); //
			break;
		}
		cista::byte_buf buffer = it ->second;
		m_commandsBuffer.erase( it );
		if ( !co_await async_write_( *m_socketPtr, buffer ) ) {
			printf( "[exchanger::Holder::finish] fail async_write_\n" ); //
			break;
		}
		printf( "[exchanger::Holder::finish] sent: %d\n", buffer.size( ) ); //
	}
	//printf( "[exchanger::serverSide] error GLE: %d\n", ::GetLastError( ) ); //
	co_return;
}
} // namespace net::tx
