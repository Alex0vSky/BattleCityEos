// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/EventExchanger.h"
namespace net::tx {
EventExchanger::EventExchanger() :
	Updater( 
			AppConfig::eventPort 
			, [this](void) mutable ->AwaitableVoid {
				for ( auto it = m_requests.begin( ); it != m_requests.end( ); ++it ) {
					const auto eventName = it ->first;
					const Buffer eventData = it ->second( );
					if ( eventData.empty( ) ) 
						continue;
					if ( !co_await Eventer::writeEvent_( Updater::getSocketClient( ), eventName, eventData ) ) {
						printf( "[EventExchanger::client] fail writeEvent_\n" ); 
						continue;
					}
				}
				co_return;
			}
			, [this](void) mutable ->AwaitableVoid {
				EventName eventName = EventName::undefined;
				Buffer eventData;
				if ( !co_await Eventer::readEvent_( Updater::getSocketServer( ), &eventName, &eventData ) ) {
					printf( "[EventExchanger::server] fail read event\n" );
					co_return;
				}
				const auto takeResponce = m_responces.find( eventName );
				if ( takeResponce == m_responces.end( ) ) {
					printf( "[EventExchanger::server] fail m_responces.find\n" );
					co_return;
				}
				if ( !eventData.empty( ) ) 
					takeResponce ->second( eventData );
				co_return;
			}
		)
{}
} // namespace net::tx
