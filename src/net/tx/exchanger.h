#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/commander.h"
namespace net::tx {
/**
 * Exchange client/server data
 */
class Exchanger : public Commander {
	using unit_t = cista::byte_buf;
	class Holder {
		std::unordered_map< Commander::Command, unit_t > m_commandsBuffer;
		tcp::acceptor *m_acceptorPtr;
	
	public:
		explicit Holder(tcp::acceptor *acceptor) : m_acceptorPtr( acceptor ) {}
		[[nodiscard]] Exchanger::Holder *Exchanger::Holder::on(Commander::Command command, unit_t const& buffer) {
			return m_commandsBuffer.emplace( command, buffer ), this;
		}
		[[nodiscard]] boost::asio::awaitable<void> finish();
	};

public:
	[[nodiscard]] boost::asio::awaitable<bool> clientSide(Commander::Command, unit_t*);
	auto Exchanger::serverSide() {
		auto p = &m_acceptor;
		return std::make_shared< Holder >( p );
	}
};
} // namespace net::tx
