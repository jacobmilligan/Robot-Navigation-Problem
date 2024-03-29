//
//  Color.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#pragma once

#include <SDL.h>

namespace robo {

/// @brief Wrapper around a series of color constants to use for the visualizer
struct Colors {
    static const SDL_Color white;
    static const SDL_Color black;
    static const SDL_Color red;
    static const SDL_Color light_green;
    static const SDL_Color orange;
    static const SDL_Color gray;
    static const SDL_Color light_gray;
    static const SDL_Color light_blue;
    static const SDL_Color green;
};


}