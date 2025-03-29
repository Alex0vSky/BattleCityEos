#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "net/type.h"

/**
 * @brief
 * Due cista::mode::WITH_VERSION
 */

namespace detail {
	using Hash = cista::hash_t;
	using MapHash = std::map< Hash, unsigned >;
}

detail::Hash type_hash(SpriteDataWrapper const& el, detail::Hash h, detail::MapHash &done) noexcept;
