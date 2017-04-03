//
//  SearchMethod.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  14/03/2017
//


#pragma once

#include "Containers.hpp"
#include "Environment.hpp"

namespace robo {

struct Solution;
class Graph;
class Environment;

/// @brief SearchResults is a struct containing the results of a search methods
/// algorithm containing success, the path taken and the amount of nodes expanded
struct SearchResults {
    SearchResults()
        : success(false), node_count(0)
    {}

    SearchResults(const bool is_succesful, const ExploredSet& explored, const Node& end);

    /// @brief Whether the search method was successful in finding a solution
    bool success;
    /// @brief The amount of children expanded
    unsigned int node_count;
    /// @brief The path taken in order
    std::vector<Node> path;
};

/// @brief SearchMethod is an abstract base class that all search methods
/// inherit from.
class SearchMethod {
public:
    /// @brief Executes the methods search algorithm
    /// @param env The environment to search
    /// @return SearchResults
    virtual SearchResults search(const Environment& env) = 0;

    /// @return Reference to the explored set
    ExploredSet& explored()
    {
        return explored_;
    }

protected:
    /// @brief The set of all explored nodes
    ExploredSet explored_;

    /// @brief Gets a child from the environment. Implemented differently for
    /// different search methods
    /// @param env The environment to get a child from
    /// @param parent The childs parent node
    /// @param action The current action being observed
    /// @return The child node
    virtual Node get_child(const Environment& env, Node& parent, const Action action);
};



}