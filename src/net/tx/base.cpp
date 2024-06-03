#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"

namespace net::tx {
Base::Base() :
	m_ioContext( 1 )
	, c_endpointClient{ boost::asio::ip::address_v4( c_host ), c_port }
	, m_acceptor( m_ioContext, c_endpointServer )
{}

void Base::update(function_t client, function_t server) {
	bool m_stop = false;
	co_spawn_( [this, server]() mutable ->awaitable {
			co_await server( reinterpret_cast< Exchanger * >( this ) );
		} );
	co_spawn_( [this, client, &m_stop]() mutable ->awaitable {
			co_await client( reinterpret_cast< Exchanger * >( this ) );
			m_stop = true;
		} );
	while ( true ) {
		m_ioContext.run_one_for( std::chrono::milliseconds{ 300 } );
		if ( m_stop ) {
			m_acceptor.cancel( );
			m_ioContext.run( );
			break;
		}
	}
}
} // namespace net::tx
