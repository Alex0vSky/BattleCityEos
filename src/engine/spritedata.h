#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
/**
 * @brief
 * A structure that stores information about a given type of object animation.
 */
struct SpriteData {
    /**
     * Position and dimensions of the first animation frame
     */
	SDL_Rect rect = { };
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
};
