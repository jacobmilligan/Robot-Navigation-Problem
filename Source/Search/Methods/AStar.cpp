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

    Node node(env.start, -1, 0, Action::none);
    if ( env.goal_test(node.state) )
        return Solution(true, explored_, node);

    frontier_.add(node);
    explored_.add(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node.state), a);
            if ( !explored_.contains(child) ) {
                if ( env.goal_test(child.state) )
                    return Solution(true, explored_, child);

                explored_.add(child);
                frontier_.add(child);
            }
        }
    }

    return Solution(false, explored_, child);
}

Node AStar::get_child(const Environment& env, const Node& parent, const Action action)
{
    auto child = SearchMethod::get_child(env, parent, action);
    auto g = parent.cost + env.step_cost;
    auto h = child.state.distance(env.goal);
    child.cost = g + h;
    return child;
}


}