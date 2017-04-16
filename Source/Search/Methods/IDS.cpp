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

    unsigned int depth = 1;
    explored_.clear();
    while ( results.cutoff ) {
        results = depth_limited_search(env, depth++);
    }

    results.solution.largest_frontier = depth;
    return results.solution;
}

IDS::IDSResults IDS::depth_limited_search(const Environment& env, const unsigned int depth)
{
    auto node = Node(env.start, nullptr, 0, Action::none);
    return recursive_dls(node, env, depth);
}

IDS::IDSResults IDS::recursive_dls(const Node& node, const Environment& env,
                                   const int depth)
{
    explored_.append(node);

    if ( env.goal_test(node.state) && depth < 1 )
        return IDSResults {
            Solution( true, explored_, &node, depth ),
            false
        };

    if ( depth < 1 )
        return IDSResults {
            Solution( false, explored_, nullptr, depth ),
            true
        };

    bool cutoff_occurred = false;
    Node child;
    IDS::IDSResults results;
    for ( auto& a : env.actions() ) {
        child = get_child(env, explored_.get(node), a);
        child.cost = depth;

        if ( !explored_.contains(child, true) ) {
            results = recursive_dls(child, env, depth - 1);

            if ( results.cutoff ) {
                cutoff_occurred = true;
            } else if ( results.solution.success ) {
                return results;
            }
        }
    }

    return IDSResults {
        Solution( false, explored_, nullptr, depth ),
        cutoff_occurred
    };
}


}
