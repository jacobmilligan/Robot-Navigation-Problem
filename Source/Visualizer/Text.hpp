//
//  Text.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  20/03/2017
//

#pragma once

#include "Visualizer/GraphicsDriver.hpp"

#include <SDL_ttf.h>
#include <Path.hpp>

namespace robo {

/// @brief Manages the lifetime of an SDL font
struct Font {
public:
    Font()
        : ttf_(nullptr), path_("")
    {}

    /// Releases all SDL memory
    ~Font();

    /// @brief Loads the font from file
    /// @param path Path to the font file
    /// @param fontsize The size to render the font at
    void load_from_file(const sky::Path& path, const int fontsize);

    /// @brief Gets a pointer to the raw font object
    /// @return Pointer to the raw font
    inline TTF_Font* ptr()
    {
        return ttf_;
    }

private:
    TTF_Font* ttf_;
    sky::Path path_;
};

/// @brief Helper class for rendering text to the window
class TextRenderer {
public:
    TextRenderer(GraphicsDriver& graphics)
        : graphics_(&graphics)
    {}

    /// @brief Draws a text string to the window using the specified font
    /// @param x X position to draw at
    /// @param y Y position to draw at
    /// @param str The string to draw
    /// @param font The font to draw with
    /// @param color The color to draw the font with
    void draw_string(const int x, const int y, const std::string& str,
                     Font& font, const SDL_Color& color);
private:
    GraphicsDriver* graphics_;
};


}



