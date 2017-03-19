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
    typedef void (* error_callback_t)(const std::string&, const std::string&);
public:
    Font()
        : ttf_(nullptr),
          path_("")
    {}

    ~Font();

    void load_from_file(const sky::Path& path, const int fontsize);

    void set_error_callback(error_callback_t error_callback);

    TTF_Font* ptr()
    {
        return ttf_;
    }

private:
    TTF_Font* ttf_;
    sky::Path path_;

    error_callback_t error_callback_;
};

class TextRenderer {
    typedef void (* error_callback_t)(const std::string&, const std::string&);
public:
    TextRenderer(GraphicsDriver& graphics)
        : graphics_(&graphics)
    {

    }

    void set_error_callback(error_callback_t error_callback);

    void draw_string(const int x,
                     const int y,
                     const std::string& str,
                     Font& font,
                     const SDL_Color& color);
private:
    GraphicsDriver* graphics_;
    error_callback_t error_callback_;
};


}



