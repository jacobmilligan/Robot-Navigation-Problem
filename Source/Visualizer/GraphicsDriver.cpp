//
//  GraphicsDriver.cpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by Jacob Milligan on 19/03/2017.
//  Copyright (c) 2017 Jacob Milligan. All rights reserved.
//

#include "Visualizer/GraphicsDriver.hpp"
#include "Visualizer/Error.hpp"

#include <SDL_ttf.h>
#include <thread>

namespace robo {


GraphicsDriver::GraphicsDriver(const std::string& app_name)
    : app_name_(app_name), clearcolor(Colors::white)
{}

GraphicsDriver::~GraphicsDriver()
{
    SDL_DestroyRenderer(renderer_);
    TTF_Quit();
}

bool GraphicsDriver::initialize(Window& window)
{
    renderer_ = SDL_CreateRenderer(window.sdl_window(),
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( renderer_ == nullptr ) {
        print_visualizer_error("SDL_CreateRenderer", SDL_GetError());
        return false;
    }

    if ( TTF_Init() != 0 ) {
        print_visualizer_error("SDL_ttf", "Initialization failed");
        return false;
    }

    return true;
}

void GraphicsDriver::clear()
{
    SDL_SetRenderDrawColor(renderer_, clearcolor.r, clearcolor.g, clearcolor.b,
                           clearcolor.a);
    SDL_RenderClear(renderer_);
}

void GraphicsDriver::set_clear_color(const SDL_Color& color)
{
    clearcolor = color;
}

void GraphicsDriver::refresh()
{
    SDL_RenderPresent(renderer_);
}

void GraphicsDriver::fill_rectangle(const SDL_Rect& rect, const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer_, &rect);
    reset_color();
}

void GraphicsDriver::draw_rectangle(const SDL_Rect& rect, const SDL_Color& color)
{
    SDL_SetRenderDrawColor(renderer_, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer_, &rect);
    reset_color();
}

SDL_Rect GraphicsDriver::get_rect(const int x, const int y, const int width,
                                  const int height)
{
    SDL_Rect rect;

    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;

    return rect;
}

void GraphicsDriver::reset_color()
{
    SDL_SetRenderDrawColor(renderer_, clearcolor.r, clearcolor.g, clearcolor.b,
                           clearcolor.a);
}

void GraphicsDriver::draw_texture(SDL_Texture* texture, const int x,
                                  const int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);
    SDL_RenderCopy(renderer_, texture, nullptr, &dest);
}

SDL_Texture* GraphicsDriver::generate_texture(SDL_Surface* surface)
{
    return SDL_CreateTextureFromSurface(renderer_, surface);
}


}