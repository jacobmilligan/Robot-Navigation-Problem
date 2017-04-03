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

#include "Search/Core/Types.hpp"

#include <vector>
#include <array>

namespace robo {

struct ExploredSet;

enum class Cell {
    empty = 0,
    start,
    goal,
    wall
};

std::string direction_to_string(const Action dir);

class Environment {
public:
    int step_cost;
    Point start;
    Point goal;

    Environment();

    Environment(const unsigned int cols, const unsigned int rows);

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

    inline const std::array<Action, 4>& actions() const
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

    inline Cell get_cell(const Point& p) const
    {
        return grid_[p.y][p.x];
    }

    inline void set_cell(const int x, const int y, const Cell cell)
    {
        grid_[y][x] = cell;
    }

    bool goal_test(const Point& pos) const;

private:
    bool valid_;
    Point size_;
    std::vector<std::vector<Cell>> grid_;

    std::array<Action, 4> actions_ = {
        {Action::up, Action::left, Action::down, Action::right}
    };
};


}