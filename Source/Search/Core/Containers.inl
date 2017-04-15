//
//  Containers.inl.hpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once

#include "Containers.hpp"

#include <set>


namespace robo {

//===============================
// Priority Queue specialization
//===============================

template <>
class Frontier<std::priority_queue> {
public:
    void clear()
    {
        while ( !_container_.empty() ) {
            _container_.pop();
        }
    }

    Node remove()
    {
        auto node = _container_.top();
        _container_.pop();
        return node;
    }

    void add(const Node& node)
    {
        _container_.push(node);
    }

    bool empty()
    {
        return _container_.empty();
    }

private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> _container_;
};

//============================
// FIFO Queue specialization
//============================

template <>
inline void Frontier<std::queue>::clear()
{
    while ( !_container_.empty() ) {
        _container_.pop();
    }
}

template <>
inline Node Frontier<std::queue>::remove()
{
    auto node = _container_.front();
    _container_.pop();
    return node;
}

template <>
inline void Frontier<std::queue>::add(const Node& node)
{
    _container_.push(node);
}

template <>
inline bool Frontier<std::queue>::empty()
{
    return _container_.empty();
}

//============================
// LIFO Queue specialization
//============================

template <>
inline void Frontier<std::vector>::clear()
{
    _container_.clear();
}

template <>
inline Node Frontier<std::vector>::remove()
{
    auto node = _container_.back();
    _container_.pop_back();
    return node;
}

template <>
inline void Frontier<std::vector>::add(const Node& node)
{
    _container_.push_back(node);
}

template <>
inline bool Frontier<std::vector>::empty()
{
    return _container_.empty();
}


}