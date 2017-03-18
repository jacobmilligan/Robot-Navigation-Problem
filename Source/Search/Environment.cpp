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

#include <sstream>

namespace robo {


std::string direction_to_string(const Direction dir)
{
    switch (dir) {
        case Direction::unknown: return "unknown";
        case Direction::none: return "none";
        case Direction::up: return "up";
        case Direction::left: return "left";
        case Direction::down: return "down";
        case Direction::right: return "right";
    }
}

SearchResults::SearchResults(const bool is_succesful, const unsigned int count, Node& end)
    : success(is_succesful), node_count(count)
{
    path.clear();
    auto node = &end;
    while ( node->parent != nullptr ) {
        path.push_back(*node);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
}

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


}