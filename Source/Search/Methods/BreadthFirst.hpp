//
//  BreadthFirst.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#pragma once

#include "Search/Core/SearchMethod.hpp"

namespace robo {

/// @brief BreadthFirst is an implementation of iterative breadth-first search
/// method
class BreadthFirst : public SearchMethod {
public:
    /// @brief Executes the breadth-first algorithm
    /// @param env The environment to search
    /// @return The results of the search
    SearchResults search(const Environment& env) override;
private:
    /// @brief The frontier, stored as a FIFO queue
    Frontier<std::queue> frontier_;
};


}

