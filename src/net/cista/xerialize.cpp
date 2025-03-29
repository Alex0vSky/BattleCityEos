// Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/xerialization.h"
#include "net/cista/typeHash.h"
#include "net/NetPlayer.h"

//template <typename Ctx> void serialize(Ctx & context, SpriteDataWrapper const* el, int offset) {
void serialize(detail::MySerCtx & context, SpriteDataWrapper const* el, int offset) {
	context.write( offset + offsetof( SpriteDataWrapper, m_sprite ), nullptr );
	cista::serialize( context, &el ->m_spriteType, offset + offsetof( SpriteDataWrapper, m_spriteType ) );
}

//void deserialize(detail::MyDesCtx const& c, SpriteDataWrapper* el) {
template <typename Ctx>
void deserialize(Ctx const& c, SpriteDataWrapper* el) {
	const auto &sc = Engine::getEngine( ).getSpriteConfig( );
	const SpriteData* spriteData = nullptr;
	const sprite_t spriteType = el ->getType( );
	if ( sprite_t::ST_NONE != spriteType )
		spriteData = sc ->getSpriteData( spriteType );
	*el = spriteData;
}

cista::byte_buf serialize_(detail::Level const& value)
{
	return cista::serialize< detail::s_mode >( value );
}

void deserialize_(cista::byte_buf const& data, detail::Level *value)
{
	*value = *cista::deserialize< detail::Level, detail::s_mode >( data );
}

cista::byte_buf serialize_(net::NetPlayer const& value)
{
	return cista::serialize< detail::s_mode >( value );
}

void deserialize_(cista::byte_buf const& data, net::NetPlayer * value)
{
	*value = *cista::deserialize< net::NetPlayer, detail::s_mode >( data );
}

cista::byte_buf serialize_(net::tx::Eventer::EventData::Shot const& value)
{
	return cista::serialize< detail::s_mode >( value );
}

void deserialize_(cista::byte_buf const& data, net::tx::Eventer::EventData::Shot *value)
{
	*value = *cista::deserialize< net::tx::Eventer::EventData::Shot, detail::s_mode >( data );
}

cista::byte_buf serialize_(net::tx::Eventer::EventData::Movement const& value)
{
	return cista::serialize< detail::s_mode >( value );
}

void deserialize_(cista::byte_buf const& data, net::tx::Eventer::EventData::Movement *value)
{
	*value = *cista::deserialize< net::tx::Eventer::EventData::Movement , detail::s_mode >( data );
}
