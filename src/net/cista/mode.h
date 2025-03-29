#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
namespace detail {
static constexpr auto s_mode = cista::mode::NONE
		| cista::mode::WITH_VERSION
		| cista::mode::WITH_INTEGRITY
		| cista::mode::DEEP_CHECK
	;
using MySerCtx = cista::serialization_context< typename cista::buf< cista::byte_buf >, (cista::mode)detail::s_mode >;
using MyDesCtx = cista::deserialization_context< (cista::mode)detail::s_mode >;
} // namespace detail
