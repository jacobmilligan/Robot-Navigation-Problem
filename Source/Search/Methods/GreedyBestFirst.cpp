//
//  GreedyBestFirst.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "GreedyBestFirst.hpp"

namespace robo {


Solution GreedyBestFirst::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, nullptr, 0, Action::none);
    if ( env.goal_test(env.start) )
        return Solution(true, explored_, &node, frontier_.largest_size());

    frontier_.add(node);
    explored_.append(node);

    Node child;
    // Run search
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        // Get all children and add to frontier if not already explored
        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node), a);
            child.cost = get_heuristic(env, child);
            if ( !explored_.contains(child) ) {
                explored_.append(child);

                if ( env.goal_test(child.state) )
                    return Solution(true, explored_, &child, frontier_.largest_size());

                frontier_.add(child);
            }
        }
    }

    return Solution(false, explored_, nullptr, frontier_.largest_size());
}

double GreedyBestFirst::get_heuristic(const Environment& env, const Node& node)
{
    return node.state.distance(env.goal, dist_func_);
}



}