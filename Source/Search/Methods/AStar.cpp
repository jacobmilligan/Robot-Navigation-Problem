//
//  AStar.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "AStar.hpp"

namespace robo {


SearchResults AStar::search(const Environment& env)
{
    frontier_clear();
    explored_.clear();

    Node node(env.start, -1, 0, Direction::none);
    if ( env.goal_test(node.state) ) {
        return SearchResults(true, explored_, node);
    }

    frontier_.push(node);
    explored_.add(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_remove();

        if ( env.goal_test(node.state) ) {
            return SearchResults(true, explored_, node);
        }

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node.state), a);
            if ( !explored_.contains(child) ) {
                explored_.add(child);

                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_, child);
                }

                frontier_.push(child);
            }
        }
    }

    return SearchResults(false, explored_, child);
}

void AStar::frontier_clear()
{
    while ( !frontier_.empty() ) {
        frontier_.pop();
    }
}

Node AStar::frontier_remove()
{
    auto node = frontier_.top();
    frontier_.pop();
    return node;
}

Node AStar::get_child(const Environment& env, Node& parent, const Direction action)
{
    auto child = SearchMethod::get_child(env, parent, action);
    auto g = parent.g + child.state.distance(parent.state);
    auto h = child.state.distance(env.goal);
    child.cost = g + h;
    return child;

}


}