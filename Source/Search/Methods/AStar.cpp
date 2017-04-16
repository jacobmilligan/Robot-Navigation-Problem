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


Solution AStar::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, nullptr, 0, Action::none);
    if ( env.goal_test(node.state) )
        return Solution(true, explored_, &node, frontier_.largest_size());

    frontier_.add(node);
    explored_.overwrite(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node), a);
            child.cost = get_heuristic(env, child);

            if ( !explored_.contains(child) ) {
                explored_.overwrite(child);

                if ( env.goal_test(child.state) )
                    return Solution(true, explored_, &child, frontier_.largest_size());

                frontier_.add(child);
            }
        }
    }

    return Solution(false, explored_, &child, frontier_.largest_size());
}

double AStar::get_heuristic(const Environment& env, const Node& node)
{
    auto parent_cost = (node.parent_ptr == nullptr) ? 0 : node.parent_ptr->cost;
    auto g = parent_cost;
    auto h = node.state.distance(env.goal, dist_func_);
    return g + h;
}


}