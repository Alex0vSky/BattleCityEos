#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/net.h"

// Empty
template <typename Ctx>
void serialize(Ctx & context, net::NetGame::element_t const* el, cista::offset_t const offset) {}

template <typename Ctx>
void serialize(Ctx & context, SpriteDataWrapper const* el, cista::offset_t const offset) {
	using cista::serialize;
	//serialize( context, &el ->m_sprite, offset + offsetof( SpriteDataWrapper, m_sprite ) );
	context.write( offset + offsetof( SpriteDataWrapper, m_sprite ), nullptr );
	serialize( context, &el ->m_spriteType, offset + offsetof( SpriteDataWrapper, m_spriteType ) );
}

template <typename Ctx>
void deserialize(Ctx const& c, net::NetGame::Level* el) {
	const auto &sc = Engine::getEngine( ).getSpriteConfig( );
	for ( auto &row : *el )
		for ( auto &col: row ) {
			if ( auto* pval = std::get_if< Object >( &col ) ) {
				deserialize( c, pval );
			}
			if ( auto* pval = std::get_if< Brick >( &col ) ) {
				deserialize( c, pval );
			}
			__nop( );
		}
}

template <typename Ctx>
void deserialize(Ctx const& c, SpriteDataWrapper* el) {
	const auto &sc = Engine::getEngine( ).getSpriteConfig( );
	const SpriteData* spriteData = nullptr;
	const sprite_t spriteType = el ->getType( );
	if ( sprite_t::ST_NONE != spriteType )
		spriteData = sc ->getSpriteData( spriteType );
	*el = spriteData;
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

	//if ( el ->m_shoots.size( ) ) {
	//	auto &bullet = el ->m_shoots[ 0 ];
	//	__nop( );
	//}
	for ( auto &bullet : el ->m_shots )
		bullet.m_sprite = sc ->getSpriteData( bullet.m_sprite.getType( ) );
}
