//
//  Containers.hpp
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

#include "Types.hpp"

#include <queue>
#include <unordered_map>
#include <cassert>
#include <limits>
#include <memory>

namespace robo {

/// @brief Frontier is an ADT representing a common interface for many
/// templated container types
template <template <typename...> class Container>
struct Frontier {
    Frontier()
        : largest_(0)
    {}

    /// @brief Clears the frontier of all nodes
    void clear();

    /// @brief Removes the next node from the frontier in the order specified
    /// by the template specialization type
    /// @return The next node in the frontier
    Node remove();

    /// @brief Adds a new node to the frontier, placing it in an order specified
    /// by the internal container type used
    /// @param node Node to add
    void add(const Node& node);

    /// @brief Checks if the frontier contains any nodes or not
    /// @return True if empty, false otherwise
    bool empty();

    /// @brief Gets a count of the size that the frontier was at its largest
    /// @return The size that the frontier was at its largest
    const unsigned long largest_size()
    {
        return largest_;
    }

private:
    Container<Node> container_;
    unsigned long largest_;
};

/// @brief Explored set is a container for storing explored nodes. Internally
/// it maintains a hashmap of indices into a vector of Node objects, allowing
/// both lookup of nodes and ordered iteration.
class ExploredSet {
public:
    /// @brief Adds a new node to the set
    /// @param node Node to add
    void append(const Node& node)
    {
        operations_.push_back(node);
        explored_[node.state].push_back(std::make_unique<Node>(node));
    }

    /// @brief Replaces all nodes in the explored set with the same state with
    /// the node passed in
    /// @param node Node to overwrite with
    void overwrite(const Node& node)
    {
        operations_.push_back(node);
        explored_[node.state].clear();
        explored_[node.state].push_back(std::make_unique<Node>(node));
    }

    /// @brief Gets the count of operations that occurred in this explored set
    /// @return Number of operations
    unsigned long num_operations() const
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
    bool contains(const Node& node, const bool cost_check = false) const
    {
        auto n  = explored_.find(node.state);

        if ( !cost_check )
            return n != explored_.end();

        if ( n != explored_.end() ) {
            for ( auto& e : n->second ) {
                auto cost = fabs(e->cost - node.cost);
                if ( cost < std::numeric_limits<double>::epsilon() )
                    return true;
            }
        }

        return false;
    }

    /// @brief Gets a node using it's state as a lookup
    /// @param node The node to find
    /// @return The node
    Node* get(const Node& node)
    {
        assert(operations_.size() > 0);

        auto result = explored_.find(node.state);
        for ( auto& n : result->second ) {
            if ( n->cost == node.cost )
                return n.get();
        }
        return result->second[0].get();
    }

    /// @brief Gets an iterator pointing to the start of the operations list
    /// @return Node vector iterator pointing to the first operation
    std::vector<Node>::iterator operations_iterator()
    {
        return operations_.begin();
    }

    /// @brief Gets the last state in the list of operations
    /// @return The last state
    const Point& last_state()
    {
        return operations_.back().state;
    }

private:
    /// @brief Maps points to indices into the operations container.
    /// For quick lookup of nodes
    std::unordered_map<Point, std::vector< std::unique_ptr<Node> >, PointHash> explored_;

    /// @brief For contiguous storage of the operations in the order they
    /// occurred
    std::vector<Node> operations_;
};



}

#include "Search/Core/Containers.inl"