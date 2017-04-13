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

#include "Search/Core/SearchMethod.hpp"


namespace robo {

/// @brief DepthFirst is an implementation of iterative depth-first search
/// method.
class DepthFirst : public SearchMethod {
public:
    DepthFirst()
        : SearchMethod("Depth-first search")
    {}
    /// @brief Searches the given environment using the depth-first algorithm
    /// @param env The environment to search
    /// @return The results of the search
    Solution search(const Environment& env) override;
private:
    /// @brief The frontier used for the search, stored as a LIFO queue
    Frontier<std::vector> frontier_;
};


}


