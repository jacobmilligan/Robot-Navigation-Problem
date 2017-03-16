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

#include "Containers/Graph.hpp"

#include <queue>
#include <unordered_map>

namespace robo {

struct Solution;
class Graph;
class Environment;

class SearchMethod {
public:
    virtual std::vector<Direction>& search(Environment& env) = 0;

    inline unsigned long size()
    {
        return explored_.size();
    }

protected:
    std::unordered_map<Point, Node, PointHash, PointEquals> explored_;
    std::vector<Direction> path_;

    void fill_path(const Node& end);
};

class BreadthFirst : public SearchMethod {
public:
    std::vector<Direction>& search(Environment& env) override;
private:
    std::queue<Node> frontier_;
};


}