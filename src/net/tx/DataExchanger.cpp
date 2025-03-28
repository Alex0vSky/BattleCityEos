// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/DataExchanger.h"
namespace net::tx {
DataExchanger::DataExchanger() : 
	Updater( 
			AppConfig::dataPort 
			, [this](void) mutable ->AwaitableVoid {
				for ( auto it = m_requests.begin( ); it != m_requests.end( ); ++it ) { 
					Buffer data;
					if ( co_await sendAndWaitResponse_( it ->first, &data ) ) 
						it ->second( data );
				}
				co_return;
			}
			, [this](void) mutable ->AwaitableVoid {
				co_await serverIteration_( );
				co_return;
			}
		)
{}

template<Commander::Command T>
void DataExchanger::setCommandHandler(CallbackClient client, CallbackServer server) {
	m_requests.insert_or_assign( T, client );
	m_responces.insert_or_assign( T, server );
}
template void DataExchanger::setCommandHandler<Commander::Command::GetFullMap>(CallbackClient, CallbackServer);
template void DataExchanger::setCommandHandler<Commander::Command::EventClientShot>(CallbackClient, CallbackServer);
template void DataExchanger::setCommandHandler<Commander::Command::Player>(CallbackClient, CallbackServer);

// TODO(alex): detect disconnection in fail writeCommand_
AwaitableBool DataExchanger::sendAndWaitResponse_(Commander::Command command, Buffer *answer) const {
	Commander::answerSize_t answerSize = 0;
	//printf( "[DataExchanger::sendAndWaitResponse_] command: %d\n", command ); //
	if ( !co_await Commander::writeCommand_( Updater::getSocketClient( ), command, &answerSize ) ) {
		printf( "[DataExchanger::sendAndWaitResponse_] fail writeCommand_\n" );
		co_return false;
	}
	if ( 0 == answerSize ) {
		//printf( "[DataExchanger::sendAndWaitResponse_] empty\n" );
		co_return false;
	}
	if ( !co_await async_read_( Updater::getSocketClient( ), answer, answerSize ) ) {
		printf( "[DataExchanger::sendAndWaitResponse_] fail async_read_\n" );
		co_return false;
	}
	printf( "[DataExchanger::sendAndWaitResponse_] read: %d/%d\n", answerSize, answer ->size( ) ); //
	co_return !answer ->empty( );
}

AwaitableVoid DataExchanger::serverIteration_() const {
	while ( Updater::getSocketServer( ).available( ) > 0 ) {
		Commander::Command remoteCommand;
		if ( !co_await Commander::readCommand_( Updater::getSocketServer( ), &remoteCommand ) )
			printf( "[DataExchanger::serverIteration_] fatal error, network 1" );
		//printf( "[DataExchanger::serverIteration_] remoteCommand: %d\n", remoteCommand ); //
		const auto availableCommand = m_responces.find( remoteCommand );
		if ( availableCommand == m_responces.end( ) ) 
			printf( "[DataExchanger::serverIteration_] fatal error, fail m_responces.find\n" ); 
		const Buffer data = availableCommand ->second( );
		if ( !co_await Commander::writeData_( Updater::getSocketServer( ), data ) )
			printf( "[DataExchanger::serverIteration_] fatal error, network 2" );
		if ( data.size( ) ) printf( "[DataExchanger::serverIteration_] sent: %d\n", data.size( ) ); //
	}
	co_return;
}
} // namespace net::tx
