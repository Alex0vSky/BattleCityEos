#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/base.h"
namespace net::tx {
/**
 * Update logic
 */
template<typename T>
class Updater : public Base {
	static constexpr boost::asio::ip::address_v4::bytes_type c_host{ 127, 0, 0, 1 };
	static constexpr auto c_runForDuration = std::chrono::milliseconds( 1 );
	using function_t = std::function< boost::asio::awaitable< void > (T *) >;

	boost::asio::io_context *m_ioContextPtr = nullptr;
	std::unique_ptr< tcp::acceptor > m_acceptor;
	const tcp::endpoint c_endpointClient, c_endpointServer;
	T *m_child;
	function_t m_client, m_server;
	bool m_isClient, m_isServer;

	void connectionEnsurance_() {
		if ( !m_socketClient )
			m_socketClient = std::make_unique< tcp::socket >( *m_ioContextPtr );
		if ( !m_socketServer )
			m_socketServer = std::make_unique< tcp::socket >( *m_ioContextPtr );
		bool run = false;
		if ( run |= ( m_isClient && !m_socketClient ->is_open( ) ) ) 
			co_spawn_( [this]() mutable ->awaitable { 
					do co_await m_socketClient ->async_connect( c_endpointClient, c_tuple );
					while ( !m_socketClient ->is_open( ) && sleep_( ) );
					__nop( );
				} );

		if ( run |= ( m_isServer && !m_socketServer ->is_open( ) ) ) 
			co_spawn_( [this]() mutable ->awaitable { 
					m_acceptor = std::make_unique< tcp::acceptor >( *m_ioContextPtr );
					m_acceptor ->open( c_endpointServer.protocol( ) );
					m_acceptor ->bind( c_endpointServer );
					m_acceptor ->listen( ñ_logbackAcceptorListen );
					do {
						tcp::socket socket = std::get< 1 >( co_await m_acceptor ->async_accept( c_tuple ) );
						*m_socketServer = std::move( socket );
					} while ( !m_socketServer ->is_open( ) && sleep_( ) );
					__nop( );
				} );
		if ( !run )
			return;
		if ( !std::is_same_v< class EventExchanger, T > )
			__nop( );
		m_ioContextPtr ->run( ), m_ioContextPtr ->restart( );
		if ( m_isServer )
			co_spawn_( [this]() mutable ->awaitable { 
					do co_await m_server( m_child ); while ( sleep_( ) );
				} );
		if ( m_isClient )
			co_spawn_( [this]() mutable ->awaitable { 
					do co_await m_client( m_child ); while ( sleep_( ) );
				} );
		__nop( );
	}

protected:
    /**
     * Create network transmission
     */
	Updater(boost::asio::io_context *ioContext, u_short port, std::optional< bool > isServer) : 
		Base( ioContext )
		, m_ioContextPtr( ioContext )
		, c_endpointClient{ boost::asio::ip::address_v4( c_host ), port }
		, c_endpointServer{ tcp::v4( ), port }
		, m_child( reinterpret_cast< T * >( this ) )
		, m_isClient( !isServer.has_value( ) || !isServer.value( ) )
		, m_isServer( !isServer.has_value( ) || isServer.value( ) )
	{}
	std::unique_ptr< tcp::socket > m_socketClient, m_socketServer;


public:
    /**
     * Call client and server simultaneously
     */
	void update() {
		connectionEnsurance_( );
		m_ioContextPtr ->poll( );
	}

	void setUpdateCallbacks(function_t client, function_t server) {
		m_client = ( client ), m_server = ( server );
	}
};
} // namespace net::tx
