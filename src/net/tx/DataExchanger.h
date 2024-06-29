#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/updater.h"
#include "net/tx/commander.h"
namespace net::tx {
/**
 * Exchange client/server data
 */
class DataExchanger : public Updater< DataExchanger >, public Commander {
	static constexpr u_short c_port = 55555;
	boost::asio::io_context m_ioContext;
	class Holder {
		commandsBuffer_t m_commandsBuffer;
		tcp::socket *m_socketPtr;
	
	public:
		explicit Holder(tcp::socket *socket) : m_socketPtr( socket ) {}
		[[nodiscard]] Holder *on(Commander::Command command, unit_t const& buffer) {
			return m_commandsBuffer.insert_or_assign( command, buffer ), this;
		}
		[[nodiscard]] boost::asio::awaitable<void> finish();
	};

public:
	DataExchanger(std::optional< bool > isServer = { }) : 
		Updater< DataExchanger >( &m_ioContext, c_port, isServer )
		, Commander( &m_ioContext )
	{}
	[[nodiscard]] boost::asio::awaitable<bool> clientSide(Commander::Command, unit_t*);
	auto DataExchanger::serverSide() {
		auto p = m_socketServer.get( );
		return std::make_shared< Holder >( p );
	}
};
} // namespace net::tx
