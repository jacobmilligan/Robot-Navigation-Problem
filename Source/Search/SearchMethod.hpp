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


class SearchMethod {
public:
    virtual SearchResults search(const Environment& env) = 0;

    inline unsigned long size()
    {
        return explored_.size();
    }

protected:
    std::unordered_map<Point, Node, PointHash, PointEquals> explored_;
};

class BreadthFirst : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
private:
    std::queue<Node> frontier_;
};

class DepthFirst : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
private:
    std::vector<Node> frontier_;
};


}