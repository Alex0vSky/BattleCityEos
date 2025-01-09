#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/Reader.h"
#include "net/tx/abstraction/Writer.h"
#include "net/EnumCheck.h"
namespace net::tx {
/**
 * Send and receive commands
 */
class Commander : protected abstraction::Reader, protected abstraction::Writer {

public:
	using TypeCommand = uint32_t;
	/**
	 * Commands set
	 */
	enum class Command : TypeCommand { undefined_
			, GetFullMap
			, GetEventServer
			, EventClientShot
			, Player // tmp
			, Something
		//, last_ , count_ = (last_ - undefined_ - 1)
		, invalid_ };
	using Valid = EnumCheck< Command
			, Command::GetFullMap
			, Command::GetEventServer 
			, Command::EventClientShot 
			, Command::Player // tmp
			, Command::Something 
		>;
	enum class Response : TypeCommand { undefined_
			, Success
			, InvalidCommand
		};

protected:
	using answerSize_t = uint32_t;
	using commandsBuffer_t = std::unordered_map< Command, Buffer >;
	static AwaitableBool readCommand_(Socket &socket, Command *command);
	static AwaitableBool writeCommand_(Socket &socket, Command command, answerSize_t *answerSize);
	static AwaitableBool writeData_(Socket &socket, Buffer const&);
};
} // namespace net::tx
