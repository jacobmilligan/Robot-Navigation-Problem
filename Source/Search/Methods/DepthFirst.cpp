//
//  DepthFirst.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Search/Methods/DepthFirst.hpp"

namespace robo {


Solution DepthFirst::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, nullptr, 1, Action::none);
    if ( env.goal_test(env.start) )
        return Solution(true, explored_, &node, frontier_.largest_size());

    frontier_.add(node);
    explored_.overwrite(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        // Get all children and add to frontier if not already explored
        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node), a);
            if ( !explored_.contains(child) ) {
                explored_.overwrite(child);

                if ( env.goal_test(child.state) )
                    return Solution(true, explored_, &child, frontier_.largest_size());

                frontier_.add(child);
            }
        }
    }

    return Solution(false, explored_, nullptr, frontier_.largest_size());
}


}