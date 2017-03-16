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

#include "Search/SearchMethod.hpp"
#include "Environment.hpp"

#include <algorithm>

namespace robo {


std::vector<Direction>& BreadthFirst::search(Environment& env)
{
    Node node(env.start, nullptr, 0, Direction::none);
    if ( env.goal_test(env.start) ) {
        path_.push_back(Direction::none);
        return path_;
    }

    frontier_.push(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.front();
        frontier_.pop();
        explored_[node.state] = node;

        for ( auto& a : env.actions() ) {
            child = env.get_child(node, a);
            child.parent = &explored_[node.state];

            if ( explored_.find(child.state) == explored_.end() ) {
                if ( env.goal_test(child.state) ) {
                    fill_path(child);
                    return path_;
                }

                frontier_.push(child);
            }
        }
    }

    path_.clear();
    path_.push_back(Direction::unknown);
    return path_;
}

void SearchMethod::fill_path(const Node& end)
{
    auto node = &end;
    while ( node->parent != nullptr ) {
        path_.push_back(node->action);
        node = node->parent;
    }
    std::reverse(path_.begin(), path_.end());
}


}