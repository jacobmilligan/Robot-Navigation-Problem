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
#include "SearchMethod.hpp"

#include <sstream>

namespace robo {


std::string direction_to_string(const Action dir)
{
    switch (dir) {
        case Action::unknown: return "unknown";
        case Action::none: return "none";
        case Action::up: return "up";
        case Action::left: return "left";
        case Action::down: return "down";
        case Action::right: return "right";
    }
}

Environment::Environment()
    : step_cost(0), valid_(false)
{}

Environment::Environment(const unsigned int cols, const unsigned int rows)
    : step_cost(0), valid_(true), size_(cols, rows)
{
    grid_.resize(rows);
    for ( auto& row : grid_ ) {
        row.resize(cols);
    }
}


bool Environment::goal_test(const Point& pos) const
{
    return grid_[pos.y][pos.x] == Cell::goal;
}


}