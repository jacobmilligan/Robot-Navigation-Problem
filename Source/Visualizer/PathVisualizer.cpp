//
//  PathVisualizer.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  20/03/2017
//

#include "Visualizer/PathVisualizer.hpp"

namespace robo {


void PathVisualizer::draw(const Solution& results, const Node& current,
                          const Environment& env)
{
    if ( current.state != env.goal )
        return;

    SDL_Rect rect;
    for ( auto& n : results.path ) {
        rect.x = n.state.x * tilesize_;
        rect.y = n.state.y * tilesize_;
        rect.w = tilesize_;
        rect.h = tilesize_;

        if ( visited_.find(n.state) != visited_.end() )
            graphics_->fill_rectangle(rect, Colors::green);
    }
}

void PathVisualizer::draw_evaluating()
{
    graphics_->fill_rectangle(current_, Colors::orange);
}

void PathVisualizer::draw_endpoints()
{
    graphics_->fill_rectangle(start_, Colors::red);
    graphics_->fill_rectangle(goal_, Colors::light_green);
}

void PathVisualizer::update_start_position(Environment& env, const int x, const int y)
{
    env.set_cell(env.start.x, env.start.y, Cell::empty);
    start_.x = x * tilesize_;
    start_.y = y * tilesize_;
    env.start = Point(x, y);
    env.set_cell(x, y, Cell::start);
}

void PathVisualizer::update_goal_position(Environment& env, const int x, const int y)
{
    env.set_cell(env.goal.x, env.goal.y, Cell::empty);
    goal_.x = x * tilesize_;
    goal_.y = y * tilesize_;
    env.goal = Point(x, y);
    env.set_cell(x, y, Cell::goal);
}

void PathVisualizer::update_current_node_position(const int x, const int y)
{
    current_.x = x * tilesize_;
    current_.y = y * tilesize_;
    visited_[Point(x, y)] = true;
}

void PathVisualizer::update_walls(Environment& env, const int x, const int y)
{
    if ( !is_endpoint(env, x, y) )
        env.set_cell(x, y, Cell::wall);
}

void PathVisualizer::toggle_wall(Environment& env, const int x, const int y)
{
    auto cell = env.get_cell(Point(x, y));
    auto new_val = ( cell == Cell::wall ) ? Cell::empty : Cell::wall;
    env.set_cell(x, y, new_val);
}

bool PathVisualizer::is_endpoint(Environment& env, const int x, const int y)
{
    return ( x == env.start.x && y == env.start.y )
        || ( x == env.goal.x && y == env.goal.y );
}


}