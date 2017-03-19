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
#include "Visualizer/Text.hpp"

#include <unordered_map>

namespace robo {

void print_error(const std::string& type, const std::string& msg);

class VisualizerApp {
public:
    VisualizerApp(const std::string& app_name, const int speed, const int tilesize, char** argv);

    void run();

private:
    using MethodMap = std::unordered_map<std::string, std::unique_ptr<robo::SearchMethod>>;

    std::string app_name_;
    Window window_;
    GraphicsDriver graphics_;
    TextRenderer text_;
    Font font_;

    SDL_Event event_;

    bool is_evaluating_;
    bool is_start_moving_;
    bool is_goal_moving_;
    bool placing_walls_;
    int tilesize_ = 64;
    int speed_ = 2;
    int timer_;
    int current_node_;

    SDL_Rect start_;
    SDL_Rect goal_;
    SDL_Rect node_rect_;

    std::unordered_map<Point, bool, PointHash> visited_;
    MethodMap methods_;

    Environment env_;
    SearchResults results_;
    robo::SearchMethod* current_method_;
    std::string method_str_;
    sky::Path root_;

    void initialize();
    void process_input();
    void update();
    void draw();

    void draw_tiles();
    void draw_path();
    void update_path();

    void toggle_wall();
    void batch_place_walls();

    SDL_Rect get_tile(const int x, const int y);
};


}


