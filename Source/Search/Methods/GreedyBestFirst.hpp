//
//  GreedyBestFirst.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#pragma once

#include "Search/SearchMethod.hpp"

namespace robo {

/// @brief GreedyBestFirst is an implementation of iterative greedy best-first
/// search method
class GreedyBestFirst : public SearchMethod {
public:
    /// @brief Searches the given environment using the greedy best-first
    /// algorithm
    /// @param env Environment to search
    /// @return The results of the search
    SearchResults search(const Environment& env) override;
protected:
    /// @brief Gets a child and it's heuristic value from the environment based
    /// off the current action. Uses euclidean distance as a heuristic
    /// @param env The environment to get the child from
    /// @param parent The parent of the child
    /// @param action The action being taken
    /// @return The child node
    Node get_child(const Environment& env, Node& parent, const Direction action) override
    {
        auto result = SearchMethod::get_child(env, parent, action);
        result.cost = result.state.distance(env.goal);
        return result;
    }

    /// @brief Clears the frontier of all nodes
    void frontier_clear() override
    {
        while ( !frontier_.empty() ) {
            frontier_.pop();
        }
    }

    /// @brief Removes the next node from the top of the queue
    /// @return The next node
    Node frontier_remove() override
    {
        auto node = frontier_.top();
        frontier_.pop();
        return node;
    }
private:
    /// @brief The frontier, stored as a priority queue, ordered by lowest cost
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier_;
};


}



