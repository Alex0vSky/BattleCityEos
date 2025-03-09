#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "spritedata.h"

/**
  * @brief
  * The class stores information about all types of animations in the game.
  */
class SpriteConfig {
    /**
     * Container storing all types of animations.
     */
	std::map<sprite_t, SpriteData> m_configs;

public:
	SpriteConfig();
    /**
     * Get the selected animation type.
     * @param sp - the type of animation you are looking for
     * @return the animation of the given type
     */
	const SpriteData* getSpriteData(sprite_t st) const {
		return &m_configs.at(st);
	}
};