//
//  IDAStar.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  06/04/2017
//

#pragma once

#include "Search/Core/SearchMethod.hpp"

namespace robo {

/// @brief AStar is an implementation of iterative A* search method for graph-based
/// environments
class IDAStar : public SearchMethod {
public:
    IDAStar()
        : dist_func_(DistanceFunction::manhattan),
          SearchMethod("Iterative-deepening A* search")
    {}

    IDAStar(const DistanceFunction distance_function)
        : dist_func_(distance_function),
          SearchMethod("Iterative-deepening A* search")
    {}
    /// @brief Executes A* on an environment
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    /// @brief Wrapper around an f-limit and a solution
    struct IDAResults {
        double limit;
        Solution solution;
    };

    /// @brief Executes IDA* recursively until the limit is reached
    /// @param env The environment to search
    /// @param node The next node in the search
    /// @param limit The current f-limit
    /// @return The results of the search
    IDAStar::IDAResults ida(const Environment& env, const Node& node, const double limit);

    Frontier<std::priority_queue> frontier_;
    ExploredSet current_;
    std::unordered_map<Point, double, PointHash> tentative_;
    DistanceFunction dist_func_;
	const double infinity_ = std::numeric_limits<double>::max();

};


}



