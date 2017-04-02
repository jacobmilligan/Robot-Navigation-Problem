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

#include "Search/SearchMethod.hpp"

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
    std::queue<Node> frontier_;

    /// @brief Clears the search methods implementation-specific frontier
    /// container
    void frontier_clear() override
    {
        while ( !frontier_.empty() ) {
            frontier_.pop();
        }
    }

    /// @brief Removes the next node from the front of the frontier
    /// @return The next node in the queue
    Node frontier_remove() override
    {
        auto node = frontier_.front();
        frontier_.pop();
        return node;
    }
};


}

