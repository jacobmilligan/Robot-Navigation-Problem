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

namespace robo {


template <template <typename...> class Container>
struct Frontier {
    Container<Node> _container_;

    void clear();

    Node remove();

    void add(const Node& node);

    bool empty();

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
        auto n  = explored_.find(node.state);
        return n != explored_.end();
    }

    /// @brief Gets a node using it's state as a lookup
    /// @param state State to get a node from
    /// @return The node
    Node& get(const Point& state)
    {
        assert(operations_.size() > 0);

        auto index = explored_[state];
        return operations_[index];
    }

    /// @brief Gets a node by ID (index)
    /// @param id ID of the node to retrieve
    /// @return The node
    const Node& get(const int id) const
    {
        assert(operations_.size() > 0);

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



}

#include "Search/Core/Containers.inl"