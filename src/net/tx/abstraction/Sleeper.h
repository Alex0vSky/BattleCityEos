#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/shortening_.h"
namespace net::tx::abstraction {
/**
 * Wrapping boost::asio sleep
 */
class Sleeper {
	IoContext *m_ioContextPtrSleeper = nullptr;

protected:
	Sleeper(IoContext *ioContext);

	bool sleep_() const;
	AwaitableBool co_sleep_() const;
};
} // namespace net::tx::abstraction
