//
//  Environment.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  16/03/2017
//

#include "Environment.hpp"

namespace robo {


Environment::Environment()
    : valid_(false), step_cost(0)
{}

Environment::Environment(const unsigned int cols, const unsigned int rows)
    : valid_(true), size_(cols, rows), step_cost(0)
{
    grid_.resize(rows);
    for ( auto& row : grid_ ) {
        row.resize(cols);
    }
}

std::string Environment::to_string()
{
    std::stringstream ss;
    for ( auto& c : grid_ ) {
        for ( auto& r : c ) {
            ss << static_cast<int>(r) << " ";
        }
        ss << "\n";
    }
    return ss.str();
}


bool Environment::goal_test(const Point& pos) const
{
    return grid_[pos.y][pos.x] == Cell::goal;
}

Node Environment::get_child(const Node& parent, const Direction action) const
{
    auto child = parent;
    child.action = action;
    child.cost = parent.cost + step_cost;
    switch (action) {
        case Direction::up:
            child.state.y -= 1;
            break;
        case Direction::left:
            child.state.x -= 1;
            break;
        case Direction::down:
            child.state.y += 1;
            break;
        case Direction::right:
            child.state.x += 1;
            break;
        default:
            child = parent;
    }

    if ( passable(child.state) )
        return child;

    return parent;
}


}