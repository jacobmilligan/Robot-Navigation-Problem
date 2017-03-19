//
//  BreadthFirst.hpp
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


class BreadthFirst : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
private:
    std::queue<Node> frontier_;

    void frontier_clear() override
    {
        while ( !frontier_.empty() ) {
            frontier_.pop();
        }
    }

    Node frontier_remove() override
    {
        auto node = frontier_.front();
        frontier_.pop();
        return node;
    }
};


}

