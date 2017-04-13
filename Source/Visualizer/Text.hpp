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


struct Font {
public:
    Font()
        : ttf_(nullptr), path_("")
    {}

    ~Font();

    void load_from_file(const sky::Path& path, const int fontsize);

    inline TTF_Font* ptr()
    {
        return ttf_;
    }

private:
    TTF_Font* ttf_;
    sky::Path path_;
};

class TextRenderer {
public:
    TextRenderer(GraphicsDriver& graphics)
        : graphics_(&graphics)
    {}

    void draw_string(const int x, const int y, const std::string& str,
                     Font& font, const SDL_Color& color);
private:
    GraphicsDriver* graphics_;
};


}



