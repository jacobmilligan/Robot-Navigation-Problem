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

#include <unordered_map>
#include <string>
#include <memory>

namespace robo {

class Graph;
class Environment;

/// @brief SearchResults is a struct containing the results of a search methods
/// algorithm containing success, the path taken and the amount of nodes expanded
struct Solution {
    Solution()
        : success(false), node_count(0), largest_frontier(0)
    {}

    Solution(const bool is_succesful, const ExploredSet& explored,
             const Node* end, const unsigned long frontiermax);

    std::string to_string();

    /// @brief Whether the search method was successful in finding a solution
    bool success;
    /// @brief The amount of children expanded
    unsigned int node_count;

    unsigned int largest_frontier;

    /// @brief The path taken in order
    std::vector<Node> path;
};

/// @brief SearchMethod is an abstract base class that all search methods
/// inherit from.
class SearchMethod {
public:
    SearchMethod(const char* name)
        : name_(name)
    {}
    /// @brief Executes the methods search algorithm
    /// @param env The environment to search
    /// @return SearchResults
    virtual Solution search(const Environment& env) = 0;

    /// @return Reference to the explored set
    ExploredSet& explored()
    {
        return explored_;
    }

    /// @brief Gets the search methods algorithm name for printing
    /// @return The search algorithm name
    const char* name()
    {
        return name_;
    }

protected:
    /// @brief The set of all explored nodes
    ExploredSet explored_;
    const char* name_;
    const char* code_;

    /// @brief Gets a child from the environment. Implemented differently for
    /// different search methods
    /// @param env The environment to get a child from
    /// @param parent The childs parent node
    /// @param action The current action being observed
    /// @return The child node
    Node get_child(const Environment& env, const Node* parent, const Action action);
};

/// @brief Typedef mapping a string (AS, BFS, DFS etc.) to a pointer to a search method
using MethodMap = std::unordered_map<std::string, std::unique_ptr<robo::SearchMethod>>;

/// @brief Generates a map containing all the search methods
/// @return Map between strings and search methods
MethodMap generate_method_map();


}