// Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "net.h"

namespace net {
	void NetGame::update(Uint32 dt) {
		// TODO(alex): get from network
		constexpr auto MODE = cista::mode::NONE
				| cista::mode::WITH_VERSION
				| cista::mode::WITH_INTEGRITY
				| cista::mode::DEEP_CHECK
			;
		if ( m_player ) {
			std::vector< unsigned char > buffer;
			NetPlayer *player;
			buffer = cista::serialize< MODE >( *m_player );
			player = cista::deserialize< NetPlayer, MODE >( buffer );
			*m_player = *player;
			__nop( );
		}
		// Initial rewrite
		if ( !m_player ) {
			for ( auto player : Game::m_players ) 
				delete player;
			Game::m_players.clear( );

			unsigned playerIndex = 0;
			m_player = std::make_shared< NetPlayer > ( 
					AppConfig::player_starting_point.at( playerIndex ).x
					, AppConfig::player_starting_point.at( playerIndex ).y
					, sprite_t::ST_PLAYER_1
				);
			m_player ->player_keys = AppConfig::player_keys.at( playerIndex );
			++playerIndex;
			Game::m_players.push_back( m_player.get( ) );
		}

		Game::update( dt );
	}
} // namespace net

using hash_t = cista::hash_t;
hash_t type_hash(SpriteDataWrapper const& el, hash_t h,
                 std::map<hash_t, unsigned>& done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}

template <typename Ctx>
inline void serialize(Ctx & context, SpriteDataWrapper const* el, cista::offset_t const offset) {
	using cista::serialize;
	serialize( context, &el ->m_sprite, offset + offsetof( SpriteDataWrapper, m_sprite ) );
	serialize( context, &el ->m_spriteType, offset + offsetof( SpriteDataWrapper, m_spriteType ) );
}

template <typename Ctx>
void deserialize(Ctx const& c, net::NetPlayer* el) {
	const auto &sc = Engine::getEngine().getSpriteConfig();
	sprite_t spriteType;
	el ->m_sprite = sc ->getSpriteData( el ->m_sprite.getType( ) );
	spriteType = el ->m_shield.m_sprite.getType( );
	const SpriteData* spriteData = nullptr;
	if ( sprite_t::ST_NONE != spriteType )
		spriteData = sc ->getSpriteData( spriteType );
	el ->m_shield.m_sprite = spriteData;

	for ( auto &bullet : el ->bullets )
		bullet.m_sprite = sc ->getSpriteData( bullet.m_sprite.getType( ) );
}
