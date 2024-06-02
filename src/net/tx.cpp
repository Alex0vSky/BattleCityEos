// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx.h"

namespace net {
Tx::Tx() :
	m_ioContext( std::make_unique< boost::asio::io_context >( 1 ) )
{}

Tx::~Tx()
{}

void Tx::update(Tx::funct_t f1, Tx::funct_t f2) {
	co_spawn_( [this, f1]() mutable ->awaitable {
			co_await f1( m_ioContext.get( ) );
		} );

	co_spawn_( [this, f2]() mutable ->awaitable {
			co_await f2( m_ioContext.get( ) );
		} );
	if ( m_ioContext ->stopped( ) ) 
		m_ioContext ->restart( );
	m_ioContext ->run( );
	__nop( );
}
} // namespace net
