#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"
namespace net::tx {
/**
 * Send and receive commands
 */
class Commander : public Base {
	using command_t = uint32_t;
	static constexpr size_t c_sizeof = sizeof( command_t );

public:
	/**
	 * Commands set
	 */
	enum class Command : command_t { undefined
		, GetFullMap
		, ChangeMapElement
		, Something
	};

protected:
	static boost::asio::awaitable<Command> readCommand_(Base::tcp::socket &socket);
	static boost::asio::awaitable<bool> writeCommand_(Base::tcp::socket &socket, Command command);
};
} // namespace net::tx
