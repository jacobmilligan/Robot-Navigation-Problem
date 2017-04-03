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

#include "Search/Core/SearchMethod.hpp"
#include "Visualizer/Text.hpp"
#include "Visualizer/PathVisualizer.hpp"

namespace robo {

void print_error(const std::string& type, const std::string& msg);

class InputState {
public:
    InputState() {}

    void toggle_all(const bool state);

    void toggle_walls(const Cell cell);

    inline bool moving_start()
    {
        return moving_start_;
    }

    inline bool moving_goal()
    {
        return moving_goal_;
    }

private:
    bool placing_walls_;
    bool moving_start_;
    bool moving_goal_;
};

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
    double last_time_;

    bool is_evaluating_;
    int tilesize_;
    int speed_;
    int timer_;
    int current_node_;

    PathVisualizer path_;
    InputState input_;
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

    double get_delta(const double last)
    {
        return ((SDL_GetPerformanceCounter() - last) * 1000) / SDL_GetPerformanceFrequency();
    }
};


}


