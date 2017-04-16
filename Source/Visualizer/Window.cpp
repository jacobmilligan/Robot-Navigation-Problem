//
//  Window.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Visualizer/Window.hpp"
#include "Visualizer/Error.hpp"

namespace robo {


Window::Window(const std::string& title, const int x, const int y, const int width, const int height)
    : title_(title), x_(x), y_(y), width_(width), height_(height)
{}

Window::~Window()
{
    SDL_DestroyWindow(window_);
}

bool Window::initialize()
{
    if ( !SDL_WasInit(SDL_INIT_VIDEO) ) {
        if ( SDL_Init(SDL_INIT_VIDEO) != 0 ) {
            robo::print_visualizer_error("SDL_Init", SDL_GetError());
            return false;
        }
    }

    window_ = SDL_CreateWindow(title_.c_str(), x_, y_, width_, height_, SDL_WINDOW_SHOWN);
    if ( window_ == nullptr ) {
        robo::print_visualizer_error("Window creation", SDL_GetError());
        return false;
    }

    open_ = true;
    return true;
}

bool Window::poll_events(SDL_Event& event)
{
    return SDL_PollEvent(&event) == 1;
}

bool Window::is_open()
{
    return open_;
}

void Window::close()
{
    open_ = false;
}

SDL_Window* Window::sdl_window()
{
    return window_;
}

}