#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/shortening_.h"
namespace net::tx::abstraction {
/**
 * Wrapping boost::asio sleep
 */
class Sleeper {
	IoContext *m_ioContextPtrSleeper = nullptr;

protected:
	Sleeper(IoContext *ioContext):
		m_ioContextPtrSleeper( ioContext )
	{}

	bool sleep_() const {
		auto value = boost::posix_time::milliseconds{ 1 };
		auto timer = boost::asio::deadline_timer( m_ioContextPtrSleeper ->get_executor( ), value );
		return timer.async_wait( c_tuple ), true;
	}
	AwaitableBool co_sleep_() const {
		auto minimal = boost::asio::steady_timer::clock_type::time_point::min( );
		auto timer = boost::asio::steady_timer( co_await boost::asio::this_coro::executor, minimal );
		co_return co_await timer.async_wait( c_tuple ), true;
	}
};
} // namespace net::tx::abstraction
