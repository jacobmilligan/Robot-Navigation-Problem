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

#include "Search/Environment.hpp"

#include <queue>
#include <unordered_map>

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

/// @brief Explored set is a container for storing explored nodes. Internally
/// it maintains a hashmap of indices into a vector of Node objects, allowing
/// both lookup of nodes and ordered iteration.
class ExploredSet {
public:
    /// @brief Adds a new node to the set
    /// @param node Node to add
    void add(const Node& node)
    {
        operations_.push_back(node);
        operations_.back().id = static_cast<int>(operations_.size() - 1);
        explored_[node.state] = operations_.size() - 1;
    }

    /// @brief Gets the current size of the explored set
    /// @return
    unsigned long size() const
    {
        return operations_.size();
    }

    /// @brief Clears the internal storage of all objects
    void clear()
    {
        operations_.clear();
        explored_.clear();
    }

    /// @brief Checks to see if the set contains the given node
    /// @param node Node to check for
    /// @return True if the set contains the node, false otherwise
    bool contains(const Node& node) const
    {
        return explored_.find(node.state) != explored_.end();
    }

    /// @brief Gets a node using it's state as a lookup
    /// @param state State to get a node from
    /// @return The node
    Node& get(const Point& state)
    {
        auto index = explored_[state];
        return operations_[index];
    }

    /// @brief Gets a node by ID (index)
    /// @param id ID of the node to retrieve
    /// @return The node
    const Node& get(const int id) const
    {
        return operations_[id];
    }

private:
    /// @brief Maps points to indices into the operations container.
    /// For quick lookup of nodes
    std::unordered_map<Point, unsigned long, PointHash> explored_;

    /// @brief For contiguous storage of the operations in the order they
    /// occurred
    std::vector<Node> operations_;
};

/// @brief SearchMethod is an abstract base class that all search methods
/// inherit from.
class SearchMethod {
public:
    /// @brief Executes the methods search algorithm
    /// @param env The environment to search
    /// @return SearchResults
    virtual SearchResults search(const Environment& env) = 0;

    /// @brief Gets the search methods explored set
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
    virtual Node get_child(const Environment& env, Node& parent, const Direction action);

    /// @brief Clears the search methods implementation-specific frontier
    /// container
    virtual void frontier_clear() = 0;

    /// @brief Removes a node from the search methods implementation-specific
    /// frontier container based off it's pre-defined rules.
    virtual Node frontier_remove() = 0;
};



}