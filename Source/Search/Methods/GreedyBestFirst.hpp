//
//  GreedyBestFirst.hpp
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

/// @brief GreedyBestFirst is an implementation of iterative greedy best-first
/// search method
class GreedyBestFirst : public SearchMethod {
public:
    GreedyBestFirst()
        : dist_func_(DistanceFunction::euclidean)
    {}

    GreedyBestFirst(const DistanceFunction distance_function)
        : dist_func_(distance_function)
    {}

    /// @brief Searches the given environment using the greedy best-first
    /// algorithm
    /// @param env Environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
protected:
    /// @brief Gets a child and it's heuristic value from the environment based
    /// off the current action. Uses euclidean distance as a heuristic
    /// @param env The environment to get the child from
    /// @param parent The parent of the child
    /// @param action The action being taken
    /// @return The child node
    Node get_child(const Environment& env, const Node* parent, const Action action) override
    {
        auto result = SearchMethod::get_child(env, parent, action);
        result.cost = result.state.distance(env.goal, dist_func_);
        return result;
    }
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    Frontier<std::priority_queue> frontier_;
    DistanceFunction dist_func_;
};


}



