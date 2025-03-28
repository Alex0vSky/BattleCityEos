#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "game.h"
#include "net/type.h"

namespace net {
class NetPlayer : public Player {
	using Player::Player;

public:
	using Tank::m_flags;
	using Object::m_current_frame;
	bool m_isDurty = true;

	void update(Uint32 dt) override;
	void shot();

	// or `std::list` to easy pop_back
	using shoots_t = cista::offset::vector< Bullet >;
	shoots_t getShots();
	bool getBulletOfShot(Bullet *bullet);

private:
public: // tmp
	shoots_t m_shots;

public:
	auto cista_members();
};
} // namespace net
