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

#include <vector>
#include <array>
#include <functional>
#include <cmath>

namespace robo {

struct ExploredSet;

enum class Cell {
    empty = 0,
    start,
    goal,
    wall
};

enum class Direction {
    unknown = 0,
    none,
    up,
    left,
    down,
    right
};

std::string direction_to_string(const Direction dir);

struct Point {
    Point()
        : x(0), y(0)
    {}

    Point(const int xpos, const int ypos)
        : x(xpos), y(ypos)
    {}

    bool operator==(const Point& other) const
    {
        return x == other.x && y == other.y;
    }

    double distance(const Point& other)
    {
        auto xsqr = (other.x - x) * (other.x - x);
        auto ysqr = (other.y - y) * (other.y - y);
        return sqrt(xsqr + ysqr);
    }

    int x;
    int y;
};

struct PointHash {
    size_t operator() (const Point& point) const
    {
        return (60 + std::hash<int>()(point.y))
            * 60 + std::hash<int>()(point.x);
    }
};

struct Node {
    Node()
        : id(-1),
          parent_id(-1),
          cost(0),
          action(Direction::unknown)
    {}

    Node(const Point& node_state, const int parent,
         const int path_cost, const Direction direction)
        : parent_id(parent),
          cost(path_cost),
          action(direction),
          state(node_state)
    {}

    bool operator>(const Node& rhs) const
    {
        return cost > rhs.cost;
    }

    int id;
    int parent_id;
    double g;
    double cost;
    Direction action;
    Point state;
};

struct SearchResults {
    SearchResults()
        : success(false), node_count(0)
    {}

    SearchResults(const bool is_succesful, const ExploredSet& explored, const Node& end);

    bool success;
    unsigned int node_count;
    std::vector<Node> path;
};

class Environment {
public:
    int step_cost;
    Point start;
    Point goal;

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

    inline const std::array<Direction, 4>& actions() const
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

    std::array<Direction, 4> actions_ = {{
                                             Direction::up,
                                             Direction::left,
                                             Direction::down,
                                             Direction::right
                                         }};
};


}