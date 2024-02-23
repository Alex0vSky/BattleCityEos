#pragma once // Copyright 2024 Alex0vSky (https://github.com/Alex0vSky)

[["underscore"]]

/**
 * The Acme module define types and interfaces for game objects
 **/
module Acme {

/**
 * @brief Base class for game objects
 **/
class BaseObject {
    /**
     * Number of the current animation frame.
     */
    int m_current_frame;
}

/**
 * @brief Class responsible for a single piece of wall.
 * @see BaseObject
 **/
class Brick extends BaseObject {
    /**
     * Number of times the bullets hit the wall.
     */
    int m_collision_count;
}

}