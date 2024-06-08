#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"

namespace net::tx {
Base::Base() :
	m_ioContext( 1 )
	, c_endpointClient{ boost::asio::ip::address_v4( c_host ), c_port }
	, m_acceptor( m_ioContext, c_endpointServer )
{}

void Base::update(function_t client, function_t server) {
	bool stop = false;
	if ( server )
		co_spawn_( [this, server]() mutable ->awaitable {
				co_await server( reinterpret_cast< Exchanger * >( this ) );
			} );
	else
		m_acceptor.close( );
	if ( client )
		co_spawn_( [this, client, &stop]() mutable ->awaitable {
				co_await client( reinterpret_cast< Exchanger * >( this ) );
				stop = true;
			} );
	while ( true ) {
		m_ioContext.run_one_for( std::chrono::milliseconds{ 300 } );
		if ( stop ) {
			if ( server ) {
				m_acceptor.cancel( );
				m_ioContext.run( );
			}
			break;
		}
	}
}
} // namespace net::tx
