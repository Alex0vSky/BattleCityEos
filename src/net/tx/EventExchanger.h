#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/updater.h"
#include "net/tx/eventer.h"
namespace net::tx {
/**
 * Exchange client events
 */
class EventExchanger : public Updater, public Eventer {
	using CallbackClient = std::function< Buffer () >;
	using CallbackServer = std::function< void (Buffer const&) >;
	std::unordered_map< Eventer::EventName, CallbackClient > m_requests;
	std::unordered_map< Eventer::EventName, CallbackServer > m_responces;

public:
	EventExchanger();

	template<Eventer::EventName T>
	void setCommandHandler(CallbackClient client, CallbackServer server);
};
} // namespace net::tx
