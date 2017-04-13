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

class GraphicsDriver {
public:
    GraphicsDriver(const std::string& app_name);

    ~GraphicsDriver();

    bool initialize(Window& window);

    void clear();

    void set_clear_color(const SDL_Color& color);

    void refresh();

    void draw_rectangle(const SDL_Rect& rect, const SDL_Color& color);

    void fill_rectangle(const SDL_Rect& rect, const SDL_Color& color);

    SDL_Rect get_rect(const int x, const int y, const int width,
                      const int height);

    SDL_Texture* generate_texture(SDL_Surface* surface);

    void draw_texture(SDL_Texture* texture, const int x, const int y);
private:
    std::string app_name_;
    SDL_Color clearcolor;
    SDL_Renderer* renderer_;

    void reset_color();
};


}