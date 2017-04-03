//
//  IDS.cpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "IDS.hpp"

namespace robo {


SearchResults IDS::search(const Environment& env)
{
    SearchResults results;
    auto cutoff = false;
    unsigned int depth = 0;

    while ( !cutoff ) {
        frontier_.clear();
        explored_.clear();
        cutoff = depth_limited_search(env, results, depth);
        depth++;
    }

    return results;
}

Node IDS::get_child(const Environment& env, Node& parent,
                                         const Action action)
{
    return SearchMethod::get_child(env, parent, action);
}

bool IDS::depth_limited_search(const Environment& env, SearchResults& results,
                               const unsigned int depth)
{
    Node child;
    bool cutoff_occurred = false;
    unsigned int current_limit = depth;

    Node node(env.start, -1, 0, Action::none);
    if ( env.goal_test(env.start) ) {
        results = SearchResults(true, explored_, node);
    }

    frontier_.add(node);
    explored_.add(node);

    while ( !frontier_.empty() && !cutoff_occurred ) {
        node = frontier_.remove();

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_.get(node.state), a);
            if ( !explored_.contains(child) ) {
                explored_.add(child);
                if ( env.goal_test(child.state) ) {
                    results = SearchResults(true, explored_, child);
                }

                frontier_.add(child);
            }
        }

        current_limit--;
        cutoff_occurred = current_limit <= 0;
    }

    results = SearchResults(false, explored_, child);
    return cutoff_occurred;
}


}
