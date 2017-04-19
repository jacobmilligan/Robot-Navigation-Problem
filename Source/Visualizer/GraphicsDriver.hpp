//
//  GraphicsDriver.hpp
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

#include "Visualizer/Color.hpp"
#include "Visualizer/Window.hpp"

#include <SDL.h>
#undef main

#include <string>

namespace robo {

class VisualizerApp;

/// @brief GraphicsDriver manages the lifetime of the SDL renderer and provides
/// helper functions for several graphics methods
class GraphicsDriver {
public:
    /// @brief Initializes the driver
    /// @param app_name The application name to use in error messages
    GraphicsDriver(const std::string& app_name);

    /// @brief Releases all SDL memory
    ~GraphicsDriver();

    /// @brief Initializes the SDL renderer and SDL_ttf
    /// @param window The window to associate the renderer with
    /// @return True if successful, false otherwise
    bool initialize(Window& window);

    /// @brief Clears the render context using the current clear color
    void clear();

    /// @brief Sets the color for clearing the render context
    /// @param color The color to set
    void set_clear_color(const SDL_Color& color);

    /// @brief Refreshes the render context for redrawing
    void refresh();

    /// @brief Draws an outlined rectangle to the render context
    /// @param rect Rectangle to draw
    /// @param color The color to draw the rectangle with
    void draw_rectangle(const SDL_Rect& rect, const SDL_Color& color);

    /// @brief Draws a filled rectangle to the render context
    /// @param rect Rectangle to draw
    /// @param color The color to draw the rectangle with
    void fill_rectangle(const SDL_Rect& rect, const SDL_Color& color);

    /// @brief Helper function for generating a rectangle with the given
    /// parameters
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @param width The rectangles width
    /// @param height The rectangles height
    /// @return The generated SDL_Rect
    SDL_Rect get_rect(const int x, const int y, const int width,
                      const int height);

    /// @brief Generates a new texture object for rendering fonts
    /// @param surface The surface to use for generating the texture
    /// @return Pointer to the texture
    SDL_Texture* generate_texture(SDL_Surface* surface);

    /// @brief Draws a texture to the render context
    /// @param texture Texture to draw
    /// @param x X coordinate to draw the texture at
    /// @param y Y coordinate to draw the texture at
    void draw_texture(SDL_Texture* texture, const int x, const int y);
private:
    std::string app_name_;
    SDL_Color clearcolor;
    SDL_Renderer* renderer_;

    /// @brief Resets the render contexts draw color
    void reset_color();
};


}