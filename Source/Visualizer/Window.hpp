//
//  Window.hpp
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

#include <string>
#include <iostream>

namespace robo {

class VisualizerApp;

/// @brief Window is a wrapper around an SDL window managing its resources and
/// lifetime
class Window {
public:
    /// @brief Creates a new window object
    /// @param title The title to display in the window bar
    /// @param x The windows x position
    /// @param y The windows y position
    /// @param width The width of the window
    /// @param height The height of the window
    Window(const std::string& title, const int x, const int y,
           const int width, const int height);

    /// @brief Releases all SDL resources
    ~Window();

    /// @brief Launches the window
    /// @return True if successfully launched, false otherwise
    bool initialize();

    /// @brief Polls all events that occurred for input processing
    /// @param event Struct to allocate the next event to
    /// @return True if successfully polled, false otherwise
    bool poll_events(SDL_Event& event);

    /// @brief Checks whether the window is open or not
    /// @return True if open, false otherwise
    bool is_open();

    /// @brief Closes the window
    void close();

    /// @brief Gets a pointer to the raw window object
    /// @return Pointer to the SDL window
    SDL_Window* sdl_window();
private:
    std::string title_;
    int x_;
    int y_;
    int width_;
    int height_;
    SDL_Window* window_;

    bool open_;
};


}