#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "type.h"
#include "appconfig.h"
#include "net/tx/abstraction/Sleeper.h"
#include "net/tx/abstraction/Spawner.h"
namespace net::tx {
/**
 * Update via network
 * Base class
 * Client and server side together
 * Establish/accept connection
 * Spawn client/server coro
 * Computing resource management for coro
 */
class Updater : abstraction::Sleeper, abstraction::Spawner {
	static constexpr boost::asio::ip::address_v4::bytes_type c_host{ 127, 0, 0, 1 };

	IoContext m_ioContext;
	std::unique_ptr< Acceptor > m_acceptor;
	const boost::asio::ip::tcp::endpoint c_endpointClient, c_endpointServer;
	using Callback = std::function< AwaitableVoid () >;
	Callback m_client, m_server;
	std::unique_ptr< Socket > m_socketClient, m_socketServer;

	void connectionEnsurance_();

protected:
    /**
     * Create network transmission
     */
	Updater(u_short port, Callback client, Callback server) : 
		Sleeper( &m_ioContext )
		, Spawner( &m_ioContext )
		, c_endpointClient{ boost::asio::ip::address_v4( c_host ), port }
		, c_endpointServer{ boost::asio::ip::tcp::v4( ), port }
		, m_client( client ), m_server( server )
	{}
	Socket &getSocketClient() const noexcept { 
		return *m_socketClient; }
	Socket &getSocketServer() const noexcept { 
		return *m_socketServer; }

public:
    /**
     * Call client and server simultaneously
     */
	void update();
};
} // namespace net::tx
