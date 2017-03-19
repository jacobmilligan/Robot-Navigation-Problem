//
//  VisualizerApp.hpp
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

#include "Visualizer/GraphicsDriver.hpp"
#include "Search/SearchMethod.hpp"

#include <unordered_map>

namespace robo {


class VisualizerApp {
public:
    VisualizerApp(const std::string& app_name, Environment& env,
                  ExploredSet& explored, SearchResults& results);

    void set_tilesize(const int size);
    void set_speed(const int speed);

    void run();

private:
    std::string app_name_;
    Window window_;
    GraphicsDriver graphics_;

    Environment& env_;
    ExploredSet& explored_;
    SearchResults& results_;

    SDL_Event event_;

    int tilesize_ = 64;
    int speed_ = 2;
    int timer_;
    int current_node_;

    SDL_Rect start_;
    SDL_Rect goal_;
    SDL_Rect node_rect_;

    std::unordered_map<Point, bool, PointHash> visited_;

    void process_input();
    void update();
    void draw();

    void draw_tiles();
    void draw_path();
};


}


