//
//  DepthFirst.hpp
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


class DepthFirst : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
private:
    std::vector<Node> frontier_;

    void frontier_clear() override
    {
        frontier_.clear();
    }

    Node frontier_remove() override
    {
        auto node = frontier_.back();
        frontier_.pop_back();
        return node;
    }
};


}


