#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/tx/abstraction/Reader.h"
#include "net/tx/abstraction/Writer.h"
#include "schema/cista/objects/bullet.h"
#include "net/EnumCheck.h"
namespace net::tx {
/**
 * Send and receive events
 */
class Eventer : protected abstraction::Reader, protected abstraction::Writer {
	using TypeSizeEventData = uint32_t;
	using TypeEvent = uint32_t;
	using TypePong = uint32_t;
	static constexpr unsigned c_pongSuccess = 200;
	static constexpr unsigned c_pongWrong = 400;

public:
	/**
	 * Events set
	 */
	enum class EventName : TypeEvent { undefined
			, ClientShot
			, ClientMovement
		, invalid };
	using Valid = EnumCheck< EventName
			, EventName::ClientShot
			, EventName::ClientMovement
		>;

	/**
	 * Events data
	 */
	struct EventData {
		struct Shot {
			enum class Owner {
				Player, Enemy
			};
			Owner owner;
			Bullet bullet;
		};
	};

protected:
	static AwaitableBool writeEvent_(Socket &socket, EventName, Buffer const&);
	static AwaitableBool readEvent_(Socket &socket, EventName *event, Buffer *eventData);
};
} // namespace net::tx
