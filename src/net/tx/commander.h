#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net/tx/base.h"
namespace net::tx {
/**
 * Send and receive commands
 */
class Commander : public Base {
	using command_t = uint32_t;

public:
	using Base::Base;
	/**
	 * Commands set
	 */
	enum class Command : command_t { undefined
		, GetFullMap
		, ChangeMapElement
		, Something
	};
	using answerSize_t = uint32_t;

protected:
	using unit_t = cista::byte_buf;
	using commandsBuffer_t = std::unordered_map< Commander::Command, unit_t >;
	static boost::asio::awaitable<Command> readCommand_(Base::tcp::socket &socket, commandsBuffer_t const&);
	static boost::asio::awaitable<bool> writeCommand_(Base::tcp::socket &socket, Command command, answerSize_t *answerSize);

private:
	static constexpr size_t c_sizeofCommand = sizeof( command_t );
	static constexpr size_t c_sizeofAnswer = sizeof( answerSize_t );
};
} // namespace net::tx
