#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"

namespace net::tx {
Base::Base() :
	m_ioContext( std::make_unique< boost::asio::io_context >( 1 ) )
	, c_endpointClient{ boost::asio::ip::address_v4( c_host ), c_port }
	, c_endpointServer{ tcp::v4( ), c_port }
{}

void Base::update(function_t client, function_t server) {
	m_stop = false;
	co_spawn_( [this, server]() mutable ->awaitable {
			co_await server( (Exchanger *)this );
		} );
	co_spawn_( [this, client]() mutable ->awaitable {
			co_await client( (Exchanger *)this );
			m_stop = true;
		} );
	while ( true ) {
		m_ioContext ->run_one_for( std::chrono::milliseconds{ 300 } );
		if ( m_stop ) {
			cancelAcceptor_( );
			m_ioContext ->run( );
			break;
		}
	}
}
} // namespace net::tx
