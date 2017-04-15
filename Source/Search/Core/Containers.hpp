//
//  Containers.hpp
//  robonav
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


template <template <typename...> class Container>
struct Frontier {
    Container<Node> _container_;

    void clear();

    Node remove();

    void add(const Node& node);

    bool empty();

    bool contains(const Node& node);

    const unsigned long size()
    {
        return _container_.size();
    }
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

    void overwrite(const Node& node)
    {
        operations_.push_back(node);
        explored_[node.state].clear();
        explored_[node.state].push_back(std::make_unique<Node>(node));
    }

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

    std::vector<Node>::iterator operations_iterator()
    {
        return operations_.begin();
    }

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