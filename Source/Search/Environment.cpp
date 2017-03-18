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

SearchResults::SearchResults(const bool is_succesful, const ExploredSet& explored, const Node& end)
    : success(is_succesful), node_count(explored.size())
{
    path.clear();
    auto node = end;
    while ( node.parent_id >= 0 ) {
        path.push_back(node);
        node = explored.get(node.parent_id);
    }
    std::reverse(path.begin(), path.end());
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