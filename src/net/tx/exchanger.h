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
		boost::asio::io_context *m_context;
		tcp::acceptor m_acceptor;
	
	public:
		Holder(boost::asio::io_context *context, tcp::endpoint endpoint) : 
			m_context( context ), m_acceptor( *context, endpoint )
		{}
		Exchanger::Holder *Exchanger::Holder::on(Commander::Command command, unit_t const& buffer) {
			return m_commandsBuffer.emplace( command, buffer ), this;
		}
		void cancel() {
			m_acceptor.cancel( );
		}
		boost::asio::awaitable<void> finish();
	};
	using holder_t = std::shared_ptr< Holder >;
	holder_t m_holder;
	void cancelAcceptor_() override {
		if ( m_holder ) m_holder ->cancel( ), m_holder.reset( );
	}

public:
	boost::asio::awaitable<bool> clientSide(Commander::Command, unit_t*);

	Exchanger::holder_t Exchanger::serverSide() {
		return m_holder = std::make_shared< Holder >( Base::m_ioContext.get( ), c_endpointServer );
	}
};
} // namespace net::tx
