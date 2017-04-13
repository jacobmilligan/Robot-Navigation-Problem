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
        : dist_func_(DistanceFunction::euclidean),
          SearchMethod("Greedy best-first search")
    {}

    GreedyBestFirst(const DistanceFunction distance_function)
        : dist_func_(distance_function),
          SearchMethod("Greedy best-first search")
    {}

    /// @brief Searches the given environment using the greedy best-first
    /// algorithm
    /// @param env Environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    Frontier<std::priority_queue> frontier_;
    DistanceFunction dist_func_;

    double get_heuristic(const Environment& env, const Node& node);
};


}



