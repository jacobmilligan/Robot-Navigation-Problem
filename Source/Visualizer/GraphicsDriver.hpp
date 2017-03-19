//
//  Renderer.hpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by Jacob Milligan on 19/03/2017.
//  Copyright (c) 2017 Jacob Milligan. All rights reserved.
//

#pragma once

#include "Visualizer/Color.hpp"
#include "Visualizer/Window.hpp"

#include <SDL.h>

#include <string>

namespace robo {


class GraphicsDriver {
public:
    GraphicsDriver(const std::string& app_name)
        : app_name_(app_name), clear_color_(Colors::white)
    {}

    ~GraphicsDriver()
    {
        SDL_DestroyRenderer(renderer_);
    }

    bool initialize(Window& window)
    {
        renderer_ = SDL_CreateRenderer(window.sdl_window(),
                                       -1,
                                       SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if ( renderer_ == nullptr ) {
            print_error("SDL_CreateRenderer", SDL_GetError());
            return false;
        }

        return true;
    }

    void clear()
    {
        SDL_SetRenderDrawColor(renderer_,
                               clear_color_.r,
                               clear_color_.g,
                               clear_color_.b,
                               clear_color_.a);
        SDL_RenderClear(renderer_);
    }

    void set_clear_color(const SDL_Color& color)
    {
        clear_color_ = color;
    }

    void refresh()
    {
        SDL_RenderPresent(renderer_);
    }

    void draw_rectangle(const int x, const int y, const int width, const int height,
                        const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;

        SDL_RenderDrawRect(renderer_, &rect);

        reset_color();
    }

    void fill_rectangle(const SDL_Rect& rect, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
        SDL_RenderFillRect(renderer_, &rect);
        reset_color();
    }

    void fill_rectangle(const int x, const int y, const int width, const int height,
                        const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);

        SDL_Rect rect;
        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;

        SDL_RenderFillRect(renderer_, &rect);
        reset_color();
    }

    void draw_rectangle(const SDL_Rect& rect, const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer_, &rect);
        reset_color();
    }

    void draw_line(const int x1, const int y1, const int x2, const int y2,
                   const SDL_Color& color)
    {
        SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
        SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
        reset_color();
    }

    SDL_Rect get_rect(const int x, const int y, const int width, const int height)
    {
        SDL_Rect rect;

        rect.x = x;
        rect.y = y;
        rect.w = width;
        rect.h = height;

        return rect;
    }

private:
    std::string app_name_;
    SDL_Color clear_color_;
    SDL_Renderer* renderer_;

    void print_error(const std::string& type, const std::string& msg)
    {
        std::cerr << "[" << app_name_ << "] " << type
                  << " error occurred: " << msg << std::endl;
    }

    void reset_color()
    {
        SDL_SetRenderDrawColor(renderer_,
                               clear_color_.r,
                               clear_color_.g,
                               clear_color_.b,
                               clear_color_.a);
    }
};


}