#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
// TODO(alex): renameme tx::Command = tx::Emmit
#include "net/tx/updater.h"
#include "net/tx/commander.h"
namespace net::tx {
/**
 * Exchange client/server data
 */
class DataExchanger : public Updater, public Commander {
	using CallbackClient = std::function< void (Buffer const&) >;
	using CallbackServer = std::function< Buffer () >;
	std::unordered_map< Commander::Command, CallbackClient > m_requests;
	std::unordered_map< Commander::Command, CallbackServer > m_responces;

	AwaitableVoid serverIteration_() const;
	AwaitableBool sendAndWaitResponse_(Commander::Command, Buffer*) const;

public:
	DataExchanger() : 
		Updater( 
				AppConfig::dataPort 
				, [this](void) mutable ->AwaitableVoid {
					for ( auto it = m_requests.begin( ); it != m_requests.end( ); ++it ) { 
						Buffer data;
						if ( co_await sendAndWaitResponse_( it ->first, &data ) ) 
							it ->second( data );
					}
					co_return;
				}
				, [this](void) mutable ->AwaitableVoid {
					co_await serverIteration_( );
					co_return;
				}
			)
	{}

	template<Commander::Command T>
	void setCommandHandler(CallbackClient client, CallbackServer server) {
		m_requests.insert_or_assign( T, client );
		m_responces.insert_or_assign( T, server );
	}
};
} // namespace net::tx
