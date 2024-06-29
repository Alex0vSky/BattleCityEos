#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/base.h"
namespace net::tx {
/**
 * Send and receive commands
 */
class Commander : public Base {
	using command_t = uint32_t;

public:
	/**
	 * Commands set
	 */
	enum class Command : command_t { undefined
		, GetFullMap
		, GetEventServer
		, EventClientShoot
		, Something
	};

protected:
	Commander(boost::asio::io_context *ioContext) : Base( ioContext )
	{}
	using answerSize_t = uint32_t;
	using commandsBuffer_t = std::unordered_map< Command, unit_t >;
	static boost::asio::awaitable<Command> readCommand_(Base::tcp::socket &socket, commandsBuffer_t const&);
	static boost::asio::awaitable<bool> writeCommand_(Base::tcp::socket &socket, Command command, answerSize_t *answerSize);
};
} // namespace net::tx
