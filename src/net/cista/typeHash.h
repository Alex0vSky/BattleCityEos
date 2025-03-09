#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/net.h"

using hash_t = cista::hash_t;

hash_t type_hash(net::NetPlayer const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetPlayer" ) );
}

hash_t type_hash(net::NetGame::Level const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetGame::Level" ) );
}

hash_t type_hash(net::NetGame::element_t const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash( "net::NetGame::element_t" ) );
}

hash_t type_hash(SpriteDataWrapper const& el, hash_t h, std::map< hash_t, unsigned >& done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}
