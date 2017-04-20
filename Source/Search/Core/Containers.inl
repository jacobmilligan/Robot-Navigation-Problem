//
//  Containers.inl
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//
//  --------------------------------------------------------------
//
//  Defines template specializations for the different frontier
//  container types available to search algorithms
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
    Frontier()
        : largest_(0)
    {}

    void clear()
    {
        while ( !container_.empty() ) {
            container_.pop();
        }
    }

    Node remove()
    {
        auto node = container_.top();
        container_.pop();
        return node;
    }

    void add(const Node& node)
    {
        container_.push(node);
        if ( container_.size() > largest_ ) {
            largest_ = container_.size();
        }
    }

    bool empty()
    {
        return container_.empty();
    }

    const unsigned long largest_size()
    {
        return largest_;
    }

private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> container_;
    unsigned long largest_;
};

//============================
// FIFO Queue specialization
//============================

template <>
inline void Frontier<std::queue>::clear()
{
    while ( !container_.empty() ) {
        container_.pop();
    }
}

template <>
inline Node Frontier<std::queue>::remove()
{
    auto node = container_.front();
    container_.pop();
    return node;
}

template <>
inline void Frontier<std::queue>::add(const Node& node)
{
    container_.push(node);
    if ( container_.size() > largest_ ) {
        largest_ = container_.size();
    }
}

template <>
inline bool Frontier<std::queue>::empty()
{
    return container_.empty();
}

//============================
// LIFO Queue specialization
//============================

template <>
inline void Frontier<std::vector>::clear()
{
    container_.clear();
}

template <>
inline Node Frontier<std::vector>::remove()
{
    auto node = container_.back();
    container_.pop_back();
    return node;
}

template <>
inline void Frontier<std::vector>::add(const Node& node)
{
    container_.push_back(node);
    if ( container_.size() > largest_ ) {
        largest_ = container_.size();
    }
}

template <>
inline bool Frontier<std::vector>::empty()
{
    return container_.empty();
}


}