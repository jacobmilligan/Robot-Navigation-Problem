//
//  DepthFirst.hpp
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

/// @brief DepthFirst is an implementation of iterative depth-first search
/// method.
class DepthFirst : public SearchMethod {
public:
    /// @brief Searches the given environment using the depth-first algorithm
    /// @param env The environment to search
    /// @return The results of the search
    SearchResults search(const Environment& env) override;
private:
    /// @brief The frontier used for the search, stored as a LIFO queue
    std::vector<Node> frontier_;

    /// @brief Clears the frontier of all nodes
    void frontier_clear() override
    {
        frontier_.clear();
    }

    /// @brief Removes the next node from the back of the frontier
    /// @return The next node
    Node frontier_remove() override
    {
        auto node = frontier_.back();
        frontier_.pop_back();
        return node;
    }
};


}


