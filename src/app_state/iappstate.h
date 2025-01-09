#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky), Copyright 2015-2021 (https://github.com/KrystianKaluzny/Tanks)
#include "type.h"
#include "engine/spriteconfig.h"

/**
 * @brief
 * The class is an interface from which the classes @a Game, @a Menu, @a Scores inherit
 */
struct IAppState {
    virtual ~IAppState() {}

    /**
     * The function checks whether the current game state has ended.
     * @return @a true if the current game state has ended, otherwise @a false.
     */
    virtual bool finished() const = 0;
    /**
     * A function that draws game elements belonging to a given state
     */
    virtual void draw() = 0;
    /**
     * A function that updates the status of objects and counters in the game
     * @param dt - time since the last function call in milliseconds
     */
    virtual void update(Uint32 dt) = 0;
    /**
     * Function enabling handling of events detected by the SDL2 library.
     * @param ev - pointer to the SDL_Event union storing the type and parameters of various events
     */
    virtual void eventProcess(SDL_Event* ev) = 0;
    /**
     * A function that returns the next state after the current state ends. The function should only be called if @a finished returns @a true.
     * @return next game save
     */
    virtual IAppState* nextState() = 0;
};
