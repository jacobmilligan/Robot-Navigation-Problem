//
//  Environment.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  14/03/2017
//


#pragma once

#include "Containers/Graph.hpp"

#include <sstream>
#include <vector>
#include <array>


namespace robo {

enum class Cell {
    empty = 0,
    start,
    goal,
    wall
};

struct Solution {
    Solution()
        : node_count(0)
    {}

    Solution(const unsigned int count, const Node& goal)
        : node_count(count), path(goal)
    {}

    unsigned int node_count;
    Node path;
};

class Environment {
public:
    Point start;
    int step_cost;

    Environment();

    Environment(const unsigned int cols, const unsigned int rows);

    std::string to_string();

    inline Point size()
    {
        return size_;
    }

    std::vector<Cell>& operator[](const unsigned long index)
    {
        return grid_[index];
    }

    inline bool valid()
    {
        return valid_;
    }

    inline std::array<Direction, 4>& actions()
    {
        return actions_;
    };

    inline bool in_bounds (const Point& p) const
    {
        return (p.x >= 0 && p.x < size_.x && p.y >= 0 && p.y < size_.y);
    }

    inline bool passable(const Point& p) const
    {
        return in_bounds(p) && grid_[p.y][p.x] != Cell::wall;
    }

    Node get_child(const Node& parent, const Direction action) const;

    bool goal_test(const Point& pos) const;

private:
    bool valid_;
    Point size_;
    std::vector<std::vector<Cell>> grid_;

    std::array<Direction, 4> actions_ = {
        Direction::up,
        Direction::left,
        Direction::down,
        Direction::right
    };
};


}