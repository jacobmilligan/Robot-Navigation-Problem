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

#include <string>

namespace robo {

class VisualizerApp;

class GraphicsDriver {
    typedef void (* error_callback_t)(const std::string&, const std::string&);
public:
    GraphicsDriver(const std::string& app_name);

    ~GraphicsDriver();

    bool initialize(Window& window);

    void clear();

    void set_clear_color(const SDL_Color& color);

    void refresh();

    void draw_rectangle(const int x, const int y, const int width, const int height,
                        const SDL_Color& color);
    void draw_rectangle(const SDL_Rect& rect, const SDL_Color& color);

    void fill_rectangle(const SDL_Rect& rect, const SDL_Color& color);
    void fill_rectangle(const int x, const int y, const int width, const int height,
                        const SDL_Color& color);

    void draw_line(const int x1, const int y1, const int x2, const int y2,
                   const SDL_Color& color);

    SDL_Rect get_rect(const int x, const int y, const int width, const int height);

    void set_error_callback(error_callback_t error_callback);

    SDL_Texture* generate_texture(SDL_Surface* surface)
    {
        return SDL_CreateTextureFromSurface(renderer_, surface);
    }

    void draw_texture(SDL_Texture* texture, const int x, const int y)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
        SDL_RenderCopy(renderer_, texture, nullptr, &dest);
    }
private:
    std::string app_name_;
    SDL_Color clear_color_;
    SDL_Renderer* renderer_;

    void reset_color();

    error_callback_t error_callback_;
};


}