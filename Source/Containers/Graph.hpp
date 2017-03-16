//
//  Graph.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  16/03/2017
//

#pragma once

#include <functional>
#include <vector>
#include <string>

namespace robo {


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


}


