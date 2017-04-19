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
    AStar()
        : dist_func_(DistanceFunction::manhattan), SearchMethod("A* search")
    {}

    AStar(const DistanceFunction distance_function)
        : dist_func_(distance_function), SearchMethod("A* search")
    {}

    /// @brief Executes A* on an environment
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    Frontier<std::priority_queue> frontier_;
    /// @brief The distance function used by A*
    DistanceFunction dist_func_;

    /// @brief Gets the heuristic for a given node
    /// @param env The environment being searched
    /// @param node The node to get the cost for
    /// @return The f value of the cost
    double get_heuristic(const Environment& env, const Node& node);
};


}



