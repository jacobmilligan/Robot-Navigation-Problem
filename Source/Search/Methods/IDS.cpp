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


Solution IDS::search(const Environment& env)
{
    IDS::IDSResults results;
    results.cutoff = true;

    unsigned int depth = 0;

    while ( results.cutoff ) {
        results = depth_limited_search(env, depth++);
    }

    return results.solution;
}

Node IDS::get_child(const Environment& env, const Node& parent,
                    const Action action)
{
    return SearchMethod::get_child(env, parent, action);
}

IDS::IDSResults IDS::depth_limited_search(const Environment& env, const unsigned int depth)
{
    explored_.clear();
    return recursive_dls(Node(env.start, -1, 0, Action::none), env, depth);
}

IDS::IDSResults IDS::recursive_dls(const Node node, const Environment& env,
                                   const int depth)
{
    explored_.add(node);

    IDS::IDSResults results;

    if ( env.goal_test(node.state) )
        return IDSResults { Solution(true, explored_, node), false };

    if ( depth <= 0 )
        return IDSResults { Solution(false, explored_, node), true };

    bool cutoff_occurred = false;
    Node child;
    for ( auto& a : env.actions() ) {
        child = get_child(env, explored_.get(node.state), a);

        if ( !explored_.contains(child) ) {
            results = recursive_dls(child, env, depth - 1);

            if ( results.cutoff ) {
                cutoff_occurred = true;
            } else if ( results.solution.success ) {
                return results;
            }
        }
    }

    return IDSResults { Solution(false, explored_, node), cutoff_occurred };
}


}
