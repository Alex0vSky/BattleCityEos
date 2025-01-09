#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/shortening_.h"
// TODO(alex): pass socket to ctor
namespace net::tx::abstraction {
/**
 * Wrapping boost::asio writing
 */
class Writer {
    template <typename... Args>
    static constexpr auto async_write(Args&&... args) -> decltype(boost::asio::async_write(std::forward<Args>(args)...)) {
        return boost::asio::async_write( std::forward< Args >( args )...);
    }
	template< typename T >
	using IsNotPointer = std::enable_if_t< !std::is_pointer_v< T >, bool >;

protected:
	template <typename T, IsNotPointer< T > = true>
	static AwaitableBool async_write_(Socket &socket, T const& t) {
		auto [error, n] = co_await async_write( socket, asioBuffer( &t, sizeof( t ) ), c_tuple );
		co_return ( sizeof( t ) == n && !error );
	}
	static AwaitableBool async_write_(Socket &socket, Buffer const& data) {
		auto [error, n] = co_await async_write( socket, asioBuffer( data ), c_tuple );
		co_return ( data.size( ) == n && !error );
	}
};
} // namespace net::tx::abstraction 
