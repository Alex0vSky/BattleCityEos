#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "typeHash.h"

detail::Hash type_hash(SpriteDataWrapper const& el, detail::Hash h, detail::MapHash &done) noexcept {
	return cista::hash_combine( h, cista::hash("SpriteDataWrapper") );
}
