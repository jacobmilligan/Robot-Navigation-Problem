//
//  Uninformed.hpp
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

struct ExploredSet {
    void add(const Node& node)
    {
        operations_.push_back(node);
        operations_.back().id = static_cast<int>(operations_.size() - 1);
        explored_[node.state] = operations_.size() - 1;
    }

    unsigned long size() const
    {
        return operations_.size();
    }

    void clear()
    {
        operations_.clear();
        explored_.clear();
    }

    bool contains(const Node& node) const
    {
        return explored_.find(node.state) != explored_.end();
    }

    Node& get(const Point& state)
    {
        auto index = explored_[state];
        return operations_[index];
    }

    const Node& get(const int id) const
    {
        return operations_[id];
    }

    Node* begin()
    {
        return &operations_[0];
    }

    Node* end()
    {
        return &operations_.back();
    }

private:
    std::unordered_map<Point, unsigned long, PointHash> explored_;
    std::vector<Node> operations_;
};

class SearchMethod {
public:
    virtual SearchResults search(const Environment& env);

    inline unsigned long size()
    {
        return explored_.size();
    }

    ExploredSet& explored()
    {
        return explored_;
    }

protected:
    ExploredSet explored_;

    virtual Node get_child(const Environment& env, Node& parent, const Direction action);
    virtual void frontier_add(const Node& node) = 0;
    virtual void frontier_clear() = 0;
    virtual Node frontier_remove() = 0;
    virtual bool frontier_empty() = 0;
};

class BreadthFirst : public SearchMethod {
protected:
    void frontier_clear() override
    {
        while ( !frontier_.empty() ) {
            frontier_.pop();
        }
    }

    void frontier_add(const Node& node) override
    {
        frontier_.push(node);
    }

    Node frontier_remove() override
    {
        auto node = frontier_.front();
        frontier_.pop();
        return node;
    }

    bool frontier_empty() override
    {
        return frontier_.empty();
    }

private:
    std::queue<Node> frontier_;
};

class DepthFirst : public SearchMethod {
protected:
    void frontier_clear() override
    {
        frontier_.clear();
    }

    void frontier_add(const Node& node) override
    {
        frontier_.push_back(node);
    }

    Node frontier_remove() override
    {
        auto node = frontier_.back();
        frontier_.pop_back();
        return node;
    }

    bool frontier_empty() override
    {
        return frontier_.empty();
    }
private:
    std::vector<Node> frontier_;
};

class GreedyBestFirst : public SearchMethod {
public:
protected:
    Node get_child(const Environment& env, Node& parent, const Direction action) override
    {
        auto result = SearchMethod::get_child(env, parent, action);
        result.cost = result.state.distance(env.goal);
        return result;
    }

    void frontier_clear() override
    {
        while ( !frontier_.empty() ) {
            frontier_.pop();
        }
    }

    void frontier_add(const Node& node) override
    {
        frontier_.push(node);
    }

    Node frontier_remove() override
    {
        auto node = frontier_.top();
        frontier_.pop();
        return node;
    }

    bool frontier_empty() override
    {
        return frontier_.empty();
    }
private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier_;
};



}