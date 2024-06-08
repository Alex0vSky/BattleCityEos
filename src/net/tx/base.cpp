#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"
namespace net::tx {
Base::Base(function_t client, function_t server) :
	m_ioContext( 1 )
	, c_endpointClient{ boost::asio::ip::address_v4( c_host ), c_port }
	, m_acceptor( m_ioContext )
	, m_client( client ), m_server( server )
	, m_exchanger( reinterpret_cast< Exchanger * >( this ) )
	, m_socketClient( m_ioContext ), m_socketServer( m_ioContext )
{}

void Base::update(bool isServer) {
	boost::asio::io_context::count_type count;
	if ( 
		!isServer && 
		!m_socketClient.is_open( ) ) {
		co_spawn_( [this]() mutable ->awaitable { 
				m_acceptor.open( c_endpointServer.protocol( ) ), m_acceptor.bind( c_endpointServer ), m_acceptor.listen( 1 );
				do m_socketClient = std::get< 1 >( co_await m_acceptor.async_accept( c_tuple ) );
				while ( !m_socketClient.is_open( ) && sleep_( ) );
				__nop( );
			} );
	}
	if ( 
		isServer && 
		!m_socketServer.is_open( ) ) {
		co_spawn_( [this]() mutable ->awaitable { 
				do co_await m_socketServer.async_connect( c_endpointClient, c_tuple );
				while ( !m_socketServer.is_open( ) && sleep_( ) );
				__nop( );
			} );
	}
	count = m_ioContext.run( );
	m_ioContext.restart( );
	__nop( );

	if ( !isServer )
		co_spawn_( m_client( m_exchanger ) );
	else
		co_spawn_( m_server( m_exchanger ) );
	count = m_ioContext.run( );
	__nop( );
}
} // namespace net::tx
