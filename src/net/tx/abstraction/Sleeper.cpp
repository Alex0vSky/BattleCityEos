// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/Sleeper.h"
namespace net::tx::abstraction {
bool Sleeper::sleep_() const {
	auto value = boost::posix_time::milliseconds{ 1 };
	auto timer = boost::asio::deadline_timer( m_ioContextPtrSleeper ->get_executor( ), value );
	return timer.async_wait( c_tuple ), true;
}
AwaitableBool Sleeper::co_sleep_() const {
	auto minimal = boost::asio::steady_timer::clock_type::time_point::min( );
	auto timer = boost::asio::steady_timer( co_await boost::asio::this_coro::executor, minimal );
	co_return co_await timer.async_wait( c_tuple ), true;
}
} // namespace net::tx::abstraction
