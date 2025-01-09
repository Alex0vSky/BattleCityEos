#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/shortening_.h"
namespace net::tx::abstraction {
/**
 * Wrapping boost::asio reading
 */
class Reader {
    template <typename... Args>
    static constexpr auto async_read(Args&&... args) -> decltype(boost::asio::async_read(std::forward<Args>(args)...)) {
        return boost::asio::async_read( std::forward< Args >( args )...);
    }

protected:
	template <typename T>
	static AwaitableBool async_read_(Socket &socket, T *t) {
		auto [error, n] = co_await async_read( socket, asioBuffer( t, sizeof( *t ) ), c_tuple );
		co_return ( sizeof( *t ) == n && !error );
	}
	static AwaitableBool async_read_(Socket &socket, Buffer *out, uint32_t answerSize) {
		out ->resize( answerSize );
		auto [error, n] = co_await async_read( socket, asioBuffer( out ->data( ), out ->size( ) ), c_tuple );
		co_return ( answerSize == n && !error );
	}
};
} // namespace net::tx::abstraction 
