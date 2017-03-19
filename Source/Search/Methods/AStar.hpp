//
//  AStar.hpp
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


class AStar : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
protected:
    void frontier_clear() override;
    Node frontier_remove() override;

    Node get_child(const Environment& env, Node& parent, const Direction action) override;
private:
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> frontier_;
};


}



