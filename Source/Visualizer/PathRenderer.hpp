//
//  PathRenderer.hpp
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

/// @brief PathRenderer manages the drawing of the path and expanded nodes
/// for the visalizer app
class PathRenderer {
public:
    /// Initializes the path renderer
    /// @param graphics The graphics driver to use in drawing
    /// @param tilesize The size of each tile to draw
    PathRenderer(GraphicsDriver& graphics, const int tilesize)
        : placing_walls_(false),
          tilesize_(tilesize),
          graphics_(&graphics)
    {
        start_ = graphics.get_rect(0, 0, tilesize, tilesize);
        goal_ = graphics.get_rect(0, 0, tilesize, tilesize);
        current_ = graphics.get_rect(0, 0, tilesize, tilesize);

    }

    /// @brief Sets the cell at the x and y coordinate to a wall
    /// @param env Search environment
    /// @param x X coordinate
    /// @param y Y coordinate
    void update_walls(Environment& env, const int x, const int y);

    /// @brief Toggles the given coordinate between empty and wall state
    /// @param env Search environment
    /// @param x X coordinate
    /// @param y Y coordinate
    void toggle_wall(Environment& env, const int x, const int y);

    /// Updates the position of the start state
    /// @param env Search environment
    /// @param x X coordinate
    /// @param y Y coordinate
    void update_start_position(Environment& env, const int x, const int y);

    /// @brief Updates the position of the goal state
    /// @param env Search environment
    /// @param x X coordinate
    /// @param y Y coordinate
    void update_goal_position(Environment& env, const int x, const int y);

    /// @brief Updates the position of the current node being expanded in the
    /// animated search tree - updated as the animation progresses
    /// @param x X coordinate
    /// @param y Y coordinate
    void update_current_node_position(const int x, const int y);

    /// @brief Draws the path to the window
    /// @param results The search results to use in drawing
    /// @param current The current node
    /// @param env The search environment
    void draw(const Solution& results, const Node& current,
              const Environment& env);

    /// @brief Draws the current node being evaluated
    void draw_evaluating();

    /// @brief Draws the two endpoints - start and goal state
    void draw_endpoints();

    /// @brief Checks if the point has been visited in the animation or not
    /// @param point Point to check
    /// @return True if visited, false otherwise
    inline bool has_visited(const Point& point)
    {
        return visited_.find(point) != visited_.end();
    }

    /// @brief Clears the path graphics
    inline void clear()
    {
        visited_.clear();
    }

    /// @brief Gets the size of the path animated so far
    inline unsigned long size()
    {
        return visited_.size();
    }

private:
    int tilesize_;
    bool placing_walls_;

    SDL_Rect start_;
    SDL_Rect goal_;
    SDL_Rect current_;

    /// @brief Map of all the points that have been animated so far
    std::unordered_map<Point, bool, PointHash> visited_;

    GraphicsDriver* graphics_;

    /// @brief Checks if a given point is either the start or the goal state
    /// @param env Environment being searched
    /// @param x X coordinate
    /// @param y Y coordinate
    /// @return True if endpoint, false otherwise
    bool is_endpoint(Environment& env, const int x, const int y);
};


}



