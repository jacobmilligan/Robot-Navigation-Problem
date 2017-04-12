//
//  AStar.hpp
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

/// @brief AStar is an implementation of iterative A* search method for graph-based
/// environments
class AStar : public SearchMethod {
public:
    /// @brief Executes A* on an environment
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
protected:
    /// @brief Gets the next child from the environment as well as it's heuristic
    /// cost
    /// @param env Environment to get the child from
    /// @param parent The childs parent node
    /// @param action The action being taken
    /// @return The child node
    Node get_child(const Environment& env, const Node* parent, const Action action) override;
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    Frontier<std::priority_queue> frontier_;
};


}



