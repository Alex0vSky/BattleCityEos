#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "appconfig.h"
#include "engine/renderer.h"
#include "engine/audio.h"
/**
 * @brief The class combines elements related to the operation of the program.
 */
class Engine {
	std::unique_ptr< Renderer > m_renderer;
	std::unique_ptr< SpriteConfig > m_sprite_config;
	std::unique_ptr< Audio > m_audio;

public:
    /**
     * @return a static instance of the @a Engine object
     */
	static Engine& getEngine() {
		//the engine can be accessed in any module using only the namespace and not the pointer
		static Engine engine;
		return engine;
	}
    /**
     * The function converts the given numerical value into text.
     * @param num - integer
     * @return integer as text
     */
	static std::string intToString(int num) {
		if(num == 0) return "0";

		std::string buf;
		bool negative = false;
		if(num < 0) {
			negative = true;
			num = -num;
		}
		for(; num; num /= 10) buf = "0123456789abcdef"[num % 10] + buf;
		if(negative) buf = "-" + buf;
		return buf;
	}
    /**
     * The function creates engine component objects.
     */
	void initModules() {
		m_renderer = std::make_unique< Renderer >( );
		m_sprite_config = std::make_unique< SpriteConfig >( );
		m_audio = std::make_unique< Audio >( );
	}
    /**
     * The function destroys engine component objects.
     */
	void destroyModules() {
		m_renderer.reset( ), m_sprite_config.reset( ), m_audio.reset( );
	}
    /**
     * @return pointer to a Renderer object that allows you to draw on the screen
     */
	Renderer* getRenderer() const {
		return m_renderer.get( );
	}
    /**
     * @return pointer to a SpriteConfig object storing texture information
     */
	SpriteConfig* getSpriteConfig() const {
		return m_sprite_config.get( );
	}

    /**
     * @return pointer to a Audio object that allows you to play sound
     */
	Audio* getAudio() const {
		return m_audio.get( );
	}
};
