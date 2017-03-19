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


class GreedyBestFirst : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
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

    Node frontier_remove() override
    {
        auto node = frontier_.top();
        frontier_.pop();
        return node;
    }
private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier_;
};


}



