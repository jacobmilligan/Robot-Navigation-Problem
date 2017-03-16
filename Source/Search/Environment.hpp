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

namespace robo {

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

    bool operator==(const Point& other)
    {
        return x == other.x && y == other.y;
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

struct PointEquals {
    bool operator()(const Point& lhs, const Point& rhs) const
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }
};

struct Node {
    Node() : parent(nullptr),
             cost(0),
             action(Direction::unknown)
    {}

    Node(const Point& node_state, Node* node_parent,
         const int path_cost, const Direction direction)
        : state(node_state),
          parent(node_parent),
          cost(path_cost),
          action(direction)
    {}

    int cost;
    Direction action;
    Point state;
    Node* parent;
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