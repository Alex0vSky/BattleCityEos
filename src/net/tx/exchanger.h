#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/commander.h"
namespace net::tx {
/**
 * Exchange client/server data
 */
class Exchanger : public Commander {
	class Holder {
		commandsBuffer_t m_commandsBuffer;
		tcp::socket *m_socketPtr;
	
	public:
		explicit Holder(tcp::socket *socket) : m_socketPtr( socket ) {}
		[[nodiscard]] Exchanger::Holder *Exchanger::Holder::on(Commander::Command command, unit_t const& buffer) {
			return m_commandsBuffer.emplace( command, buffer ), this;
		}
		[[nodiscard]] boost::asio::awaitable<void> finish();
	};

public:
	using Commander::Commander;
	[[nodiscard]] boost::asio::awaitable<bool> clientSide(Commander::Command, unit_t*);
	auto Exchanger::serverSide() {
		auto p = &m_socketServer;
		return std::make_shared< Holder >( p );
	}
};
} // namespace net::tx
