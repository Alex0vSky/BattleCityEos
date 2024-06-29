#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

namespace net::tx {
/**
 * Wrapping boost::asio
 */
class Base {
	template <typename... Args>
	static constexpr auto as_tuple(Args&&... args) {
		return boost::asio::experimental::as_tuple( std::forward< Args >( args )... );
	}
	static constexpr auto c_sleep = boost::posix_time::milliseconds{ 300 };

public:
	using awaitable = boost::asio::awaitable< void >;
	using awaitableBool = boost::asio::awaitable< bool >;
	using tcp = boost::asio::ip::tcp;
	// TODO(alex): make me mayor
	using socket = boost::asio::ip::tcp::socket;

protected:
	Base(boost::asio::io_context *ioContext);

	boost::asio::io_context *m_ioContextPtr = nullptr;
	using unit_t = cista::byte_buf;
	static constexpr auto c_detached = boost::asio::detached;
	static constexpr auto c_tuple = as_tuple( boost::asio::use_awaitable_t{ } );
	static constexpr int ñ_logbackAcceptorListen = 1;

	template <typename F>
	inline BOOST_ASIO_INITFN_AUTO_RESULT_TYPE( decltype( c_detached ),
		typename detail::awaitable_signature<typename result_of<F()>::type>::type)
	co_spawn_(F&& f) {
		return co_spawn( m_ioContextPtr ->get_executor( ), std::forward<F>(f), c_detached );
	}

	template <typename T>
	static boost::asio::awaitable< bool > async_read_(tcp::socket &socket, T *t) {
		auto [error, n] = co_await boost::asio::async_read( socket, boost::asio::buffer( t, sizeof( *t ) ), c_tuple );
		co_return ( sizeof( *t ) == n && !error );
	}
	static boost::asio::awaitable< bool > async_read_(tcp::socket &socket, unit_t *buffer, uint32_t answerSize) {
		buffer ->resize( answerSize );
		auto [error, n] = co_await boost::asio::async_read( socket, boost::asio::buffer( buffer ->data( ), buffer ->size( ) ), c_tuple );
		co_return ( answerSize == n && !error );
	}
	template <typename T>
	static boost::asio::awaitable< bool > async_write_(tcp::socket &socket, T *t) {
		auto [error, n] = co_await boost::asio::async_write( socket, boost::asio::buffer( t, sizeof( *t ) ), c_tuple );
		co_return ( sizeof( *t ) == n && !error );
	}
	static boost::asio::awaitable< bool > async_write_(tcp::socket &socket, unit_t const& buffer) {
		auto [error, n] = co_await boost::asio::async_write( socket, boost::asio::buffer( buffer ), c_tuple );
		co_return ( buffer.size( ) == n && !error );
	}

	bool sleep_(boost::posix_time::milliseconds sleep_ = c_sleep) {
		//return boost::asio::deadline_timer( m_ioContext, sleep_ ).async_wait( c_tuple ), true;
		//return std::this_thread::sleep_for( std::chrono::milliseconds{ 10 } ), true;
		return true;
	}
};
} // namespace net::tx
