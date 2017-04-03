//
//  PathVisualizer.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  20/03/2017
//

#pragma once

#include "Visualizer/GraphicsDriver.hpp"
#include "Search/Core/Environment.hpp"
#include "Search/Core/SearchMethod.hpp"

#include <SDL.h>

#include <unordered_map>

namespace robo {


class PathVisualizer {
public:
    PathVisualizer(GraphicsDriver& graphics, const int tilesize)
        : placing_walls_(false),
          tilesize_(tilesize),
          graphics_(&graphics)
    {
        start_ = graphics.get_rect(0, 0, tilesize, tilesize);
        goal_ = graphics.get_rect(0, 0, tilesize, tilesize);
        current_ = graphics.get_rect(0, 0, tilesize, tilesize);

    }
    void update_walls(Environment& env, const int x, const int y);
    void toggle_wall(Environment& env, const int x, const int y);
    void update_start_position(Environment& env, const int x, const int y);
    void update_goal_position(Environment& env, const int x, const int y);
    void update_current_node_position(const int x, const int y);

    void draw(const SearchResults& results, const int current, const int node_count);

    void draw_evaluating();

    void draw_endpoints();

    inline bool has_visited(const Point& point)
    {
        return visited_.find(point) != visited_.end();
    }

    inline void clear()
    {
        visited_.clear();
    }
private:
    int tilesize_;
    bool placing_walls_;

    SDL_Rect start_;
    SDL_Rect goal_;
    SDL_Rect current_;

    std::unordered_map<Point, bool, PointHash> visited_;

    GraphicsDriver* graphics_;
};


}



