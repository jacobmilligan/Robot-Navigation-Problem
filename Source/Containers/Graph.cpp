//
//  Graph.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  16/03/2017
//

#include "Graph.hpp"

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


}