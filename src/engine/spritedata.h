#pragma once // Copyright 2025 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
/**
 * @brief
 * A structure that stores information about a given type of object animation.
 */
struct SpriteData {
    /**
     * Position and dimensions of the first animation frame
     */
	rect_t rect = { };
    /**
     * Number of frames in the animation.
     */
	int frames_count = 0;
    /**
     * Display time of one frame in milliseconds.
     */
	unsigned int frame_duration = 0;
    /**
     * Variable specifying whether the animation is looped.
     */
	bool loop = false;
    /**
     * Usefull in serialization.
     */
	sprite_t type = sprite_t::ST_NONE;
};

#ifdef A0S_SCHEMA_CISTA
class SpriteDataWrapper {
	template <typename Ctx> friend void serialize(Ctx & context, SpriteDataWrapper const* el,cista::offset_t const offset);
	template <typename Ctx> friend void deserialize(Ctx const& c, SpriteDataWrapper* el);

    const SpriteData* m_sprite = nullptr;
    sprite_t m_spriteType = sprite_t::ST_NONE;

public:
	const SpriteData* operator ->() {
		return m_sprite;
	}
	operator bool() const {
		return nullptr != m_sprite;
	}
	SpriteDataWrapper& operator=(const SpriteData* sprite) {
		if ( sprite ) {
			m_spriteType = sprite ->type;
			m_sprite = sprite;
		} else {
			m_spriteType = sprite_t::ST_NONE;
			m_sprite = nullptr;
		}
		return *this;
	}
	SpriteDataWrapper& operator=(std::nullptr_t) {
		return m_spriteType = sprite_t::ST_NONE, m_sprite = nullptr, *this;
	}
	bool operator==(std::nullptr_t) const {
		return nullptr == m_sprite;
	}
	bool operator==(const SpriteData* sprite) const {
		return sprite == m_sprite;
	}
	bool operator!=(const SpriteData* sprite) const {
		return !( sprite == m_sprite );
	}
	sprite_t getType() const {
		return m_spriteType;
	}
};
#else
typedef SpriteData SpriteDataWrapper;
#endif // A0S_SCHEMA_CISTA
