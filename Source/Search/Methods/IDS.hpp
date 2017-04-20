//
//  IDS.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once


#include "Search/Core/SearchMethod.hpp"

namespace robo {


class IDS : public SearchMethod {
public:
    IDS()
        : SearchMethod("Iterative-deepening depth-first search")
    {}
    Solution search(const Environment& env) override;
private:
    /// @brief Wrapper around a cutoff depth and a solution
    struct IDSResults {
        Solution solution;
        bool cutoff;
    };

    /// @brief Executes a depth limited search as one iteration of IDDFS
    /// @param env The environment to search
    /// @param limit The depth limit to use as a cutoff
    /// @return The results of the search
    IDSResults depth_limited_search(const Environment& env, const unsigned int limit);

    /// @brief Executes a recursive depth limited search
    /// @param node The current node in the search
    /// @param env The environment being searched
    /// @param depth The current depth
    /// @return The results of the search
    IDSResults recursive_dls(const Node& node, const Environment& env,
                             const int depth);
};


}



