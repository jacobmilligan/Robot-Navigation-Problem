//
//  IterativeDeepeningSearch.cpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "IterativeDeepeningSearch.hpp"

namespace robo {


SearchResults IterativeDeepeningSearch::search(const Environment& env)
{
    frontier_.clear();
    explored_.clear();

    Node node(env.start, -1, 0, Action::none);
    if ( env.goal_test(env.start) ) {
        return SearchResults(true, explored_, node);
    }

    frontier_.add(node);
    explored_.add(node);

    Node child;
    while ( !frontier_.empty() ) {
        node = frontier_.remove();

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node.state), a);
            if ( !explored_.contains(child) ) {
                explored_.add(child);
                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_, child);
                }

                frontier_.add(child);
            }
        }
    }

    return SearchResults(false, explored_, child);
}

ExploredSet& IterativeDeepeningSearch::explored()
{
    return SearchMethod::explored();
}

Node IterativeDeepeningSearch::get_child(const Environment& env, Node& parent,
                                         const Action action)
{
    return SearchMethod::get_child(env, parent, action);
}


}
