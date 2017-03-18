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

namespace robo {


SearchResults BreadthFirst::search(const Environment& env)
{
    explored_.clear();

    Node node(env.start, nullptr, 0, Direction::none);
    if ( env.goal_test(env.start) ) {
        return SearchResults(true, explored_.size(), node);
    }

    frontier_.push(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.front();
        frontier_.pop();
        explored_[node.state] = node;

        for ( auto& a : env.actions() ) {
            child = env.get_child(explored_[node.state], a);

            if ( explored_.find(child.state) == explored_.end() ) {
                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_.size(), child);
                }

                frontier_.push(child);
            }
        }
    }

    return SearchResults(false, explored_.size(), child);
}

SearchResults DepthFirst::search(const Environment& env)
{
    Node node(env.start, nullptr, 1, Direction::none);
    if ( env.goal_test(env.start) ) {
        return SearchResults(true, explored_.size(), node);
    }

    frontier_.clear();
    explored_.clear();

    frontier_.push_back(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.back();
        frontier_.pop_back();
        explored_[node.state] = node;

        for ( auto& a : env.actions() ) {
            child = env.get_child(explored_[node.state], a);

            if ( explored_.find(child.state) == explored_.end() ) {
                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_.size(), child);
                }

                frontier_.push_back(child);
            }
        }
    }

    return SearchResults(false, explored_.size(), child);
}


}