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
        : dist_func_(DistanceFunction::euclidean)
    {}

    AStar(const DistanceFunction distance_function)
        : dist_func_(distance_function)
    {}

    /// @brief Executes A* on an environment
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    Frontier<std::priority_queue> frontier_;
    DistanceFunction dist_func_;

    double get_heuristic(const Environment& env, const Node& node);
};


}



