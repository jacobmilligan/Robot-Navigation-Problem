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


class Window {
public:
    Window(const std::string& title, const int x, const int y,
           const int width, const int height);
    ~Window();
    bool initialize();
    bool poll_events(SDL_Event& event);
    bool is_open();
    void close();
    SDL_Window* sdl_window();
private:
    std::string title_;
    int x_;
    int y_;
    int width_;
    int height_;
    SDL_Window* window_;

    bool open_;

    void print_error(const std::string& type, const std::string& msg);
};


}