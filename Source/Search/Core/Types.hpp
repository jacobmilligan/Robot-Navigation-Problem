//
//  Types.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include <functional>
#include <cmath>
#include <cstdlib>

namespace robo {

/// @brief All valid actions able to be taken in a search environment
enum class Action {
    /// @brief Represents invalid states
    unknown = 0,
    /// @brief Represents no action taken, i.e. from the start position
    none,
    up,
    left,
    down,
    right
};

/// @brief Defines a distance function to use
enum class DistanceFunction {
    euclidean,
    manhattan
};

/// @brief Point is a simple x, y coordinate in a grid
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

    bool operator!=(const Point& other) const
    {
        return !(*this == other);
    }

    /// @brief Calculates the distance from this point to another one using
    /// the distance function specified
    /// @param other The other point to get the distance to
    /// @param distance_function The distance function to use in calculation
    /// @return The distance to the point
    double distance(const Point& other,
                    const DistanceFunction distance_function) const
    {
        switch (distance_function) {

            case DistanceFunction::euclidean:
            {
                auto xsqr = (other.x - x) * (other.x - x);
                auto ysqr = (other.y - y) * (other.y - y);
                return sqrt(xsqr + ysqr);
            };
            case DistanceFunction::manhattan:
            {
                auto xresult = abs(x - other.x);
                auto yresult = abs(y - other.y);
                return xresult + yresult;
            };
        }
    }

    int x;
    int y;
};

/// @brief Hashing function for storing a point in an associative container
struct PointHash {
    size_t operator() (const Point& point) const
    {
        return (60 + std::hash<int>()(point.y))
            * 60 + std::hash<int>()(point.x);
    }
};

/// @brief Node is a node in a search tree containing its cost, action taken
/// to get to it, it's state and operator overloads for checking equality
struct Node {
    Node()
        : parent_ptr(nullptr),
          cost(0),
          action(Action::unknown)
    {}

    Node(const Point& node_state, const Node* parent,
         const int path_cost, const Action direction)
        : parent_ptr(parent),
          cost(path_cost),
          action(direction),
          state(node_state)
    {}

    bool operator>(const Node& rhs) const
    {
        return cost > rhs.cost;
    }

    bool operator<(const Node& rhs) const
    {
        return cost < rhs.cost;
    }

    const Node* parent_ptr;
    double cost;
    Action action;
    Point state;
};


}