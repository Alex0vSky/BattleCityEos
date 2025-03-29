#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky)
#include "objects/object.h"
#include "objects/brick.h"
#include "net/cista/mode.h"

namespace detail {
template<typename T> using container_t = cista::offset::vector< T >;
// default-constructed variant holds a value of its first alternative: nullptr_t
using LevelElement = cista::variant< nullptr_t, Object, Brick >;
using Level = container_t< container_t< LevelElement > >;
} // namespace detail
