#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/net.h"

namespace detail {
	using Hash = cista::hash_t;
	using MapHash = std::map< Hash, unsigned >;
}

detail::Hash type_hash(net::NetPlayer const& el, detail::Hash h, detail::MapHash &done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetPlayer" ) );
}

detail::Hash type_hash(net::NetGame::Level const& el, detail::Hash h, detail::MapHash &done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetGame::Level" ) );
}

detail::Hash type_hash(net::NetGame::element_t const& el, detail::Hash h, detail::MapHash &done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetGame::element_t" ) );
}

detail::Hash type_hash(SpriteDataWrapper const& el, detail::Hash h, detail::MapHash &done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}
