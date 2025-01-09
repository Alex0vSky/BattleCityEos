#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/updater.h"
namespace net::tx {

void Updater::connectionEnsurance_() {
	using NAP = NetworkApplicationType;
	const auto appType = AppConfig::appType;
	const bool isClient = ( NAP::IntraProcess == appType || NAP::Client == appType );
	const bool isServer = ( NAP::IntraProcess == appType || NAP::Server == appType );

	if ( !m_socketClient ) 
		m_socketClient = std::make_unique< Socket >( m_ioContext );
	if ( !m_socketServer ) 
		m_socketServer = std::make_unique< Socket >( m_ioContext );
	bool runClient, runServer; runClient = runServer = false;
	if ( runClient = ( isClient && !m_socketClient ->is_open( ) ) ) { 
		co_spawn_( [this]() mutable ->AwaitableVoid { 
				boost::system::error_code error;
				do error = std::get< 0 >( co_await m_socketClient ->async_connect( c_endpointClient, c_tuple ) );
				while ( error && co_await co_sleep_( ) );
				__nop( );
				printf( "[Updater::connectionEnsurance_] client, connected to server, pid: %d\n", boost::process::v2::current_pid( ) ); //
			} );
		printf( "[Updater::connectionEnsurance_] client, spawned, pid: %d\n", boost::process::v2::current_pid( ) ); //
	}

	if ( runServer = ( isServer && !m_socketServer ->is_open( ) ) ) { 
		co_spawn_( [this]() mutable ->AwaitableVoid { 
				m_acceptor = std::make_unique< Acceptor >( m_ioContext );
				m_acceptor ->open( c_endpointServer.protocol( ) );
				m_acceptor ->bind( c_endpointServer );
				m_acceptor ->listen( c_logback );
				do {
					Socket socket = std::get< 1 >( co_await m_acceptor ->async_accept( c_tuple ) );
					*m_socketServer = std::move( socket );
				} while ( !m_socketServer ->is_open( ) && co_await co_sleep_( ) );
				printf( "[Updater::connectionEnsurance_] server, connected client, pid: %d\n", boost::process::v2::current_pid( ) ); //
				__nop( );
			} );
		printf( "[Updater::connectionEnsurance_] server, spawned, pid: %d\n", boost::process::v2::current_pid( ) ); //
	}

	if ( !runClient && !runServer )
		return;
	m_ioContext.run( ), m_ioContext.restart( );

	if ( isServer )
		co_spawn_( [this]() mutable ->AwaitableVoid { 
				//do co_await m _server( m_child ); while ( sleep_( ) ); //do co_await m _server( m_child ); while ( true );
				do co_await m_server( ); while ( co_await co_sleep_( ) );
			} );
	if ( isClient )
		co_spawn_( [this]() mutable ->AwaitableVoid { 
				//do co_await m _client( m_child ); while ( sleep_( ) ); //do co_await m _client( m_child ); while ( true );
				do co_await m_client( ); while ( co_await co_sleep_( ) );
			} );
	__nop( );
}

void Updater::update() {
	connectionEnsurance_( );
	boost::system::error_code ec;
	//m_ioContext.poll( ec );

	//m_ioContext.poll_one( ec ); // +-
	m_ioContext.run_for( std::chrono::milliseconds{ 15 } ); // better for IntraProcess
	if ( ec )
		__nop( );
	__nop( );
}
} // namespace net::tx
