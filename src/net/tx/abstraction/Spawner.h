#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/shortening_.h"
namespace net::tx::abstraction {
/**
 * Wrapping boost::asio coro spawner
 */
class Spawner {
	IoContext *m_ioContextPtrSpawner = nullptr;

protected:
	Spawner(IoContext *ioContext):
		m_ioContextPtrSpawner( ioContext )
	{}

	template <typename F>
	inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE( decltype( c_detached ),
		typename detail::awaitable_signature<typename result_of<F()>::type>::type)
	co_spawn_(F&& f) {
		return co_spawn( m_ioContextPtrSpawner ->get_executor( ), std::forward<F>(f), c_detached );
	}
};
} // namespace net::tx::abstraction
