#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
/**
 * Shortening stuffs for boost::asio and serializer
 */
namespace net::tx {
	using AwaitableVoid = boost::asio::awaitable< void >;
	using AwaitableBool = boost::asio::awaitable< bool >;
	using Acceptor = boost::asio::ip::tcp::acceptor;
	using Socket = boost::asio::ip::tcp::socket;
	using IoContext = boost::asio::io_context;

	static constexpr auto c_detached = boost::asio::detached;
	static constexpr auto c_tuple = boost::asio::experimental::as_tuple( 
		boost::asio::use_awaitable_t{ } );
	// logback acceptor listen
	static constexpr int c_logback = 1;
    template <typename... Args>
    static constexpr auto asioBuffer(Args&&... args) -> decltype( boost::asio::buffer(std::forward<Args>(args)...) ) {
        return boost::asio::buffer( std::forward< Args >( args )...);
    }

	using Buffer = cista::byte_buf;
} // namespace net::tx
