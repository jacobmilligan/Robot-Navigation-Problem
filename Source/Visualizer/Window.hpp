//
//  SDLWindow.hpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by Jacob Milligan on 19/03/2017.
//  Copyright (c) 2017 Jacob Milligan. All rights reserved.
//

#pragma once

#include <SDL.h>

#include <string>
#include <iostream>

namespace robo {


class Window {
public:
    Window(const std::string& title, const int x, const int y,
           const int width, const int height)
        : title_(title), x_(x), y_(y), width_(width), height_(height)
    {}

    ~Window()
    {
        SDL_DestroyWindow(window_);
        SDL_Quit();
    }

    bool initialize()
    {
        if ( !SDL_WasInit(SDL_INIT_VIDEO) ) {
            if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
                print_error("SDL_Init", SDL_GetError());
                return false;
            }
        }

        window_ = SDL_CreateWindow(title_.c_str(), x_, y_, width_, height_, SDL_WINDOW_SHOWN);
        if ( window_ == nullptr ) {
            print_error("Window creation", SDL_GetError());
            return false;
        }

        open_ = true;
        return true;
    }

    bool poll_events(SDL_Event& event)
    {
        return SDL_PollEvent(&event) == 1;
    }

    bool is_open()
    {
        return open_;
    }

    void close()
    {
        open_ = false;
    }

    SDL_Window* sdl_window()
    {
        return window_;
    }

private:
    std::string title_;
    int x_;
    int y_;
    int width_;
    int height_;
    SDL_Window* window_;

    bool open_;

    void print_error(const std::string& type, const std::string& msg)
    {
        std::cerr << "[" << title_ << "] " << type
                  << " error occurred: " << msg << std::endl;
    }
};


}