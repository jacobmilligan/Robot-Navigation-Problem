//
//  IDAStar.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  06/04/2017
//

#include "IDAStar.hpp"

namespace robo {


Solution IDAStar::search(const Environment& env)
{
    auto node = Node(env.start, -1, 0, Action::none);
    node.cost = node.state.distance(env.goal);

    RBFSResults results;
    results.limit = node.state.distance(env.goal);
    while ( true ) {
        explored_.clear();
        results = ida(env, node, results.limit);
        if ( results.solution.success || results.limit >= MAXFLOAT )
            break;
    }

    return results.solution;
}

IDAStar::RBFSResults IDAStar::ida(const Environment& env, const Node& node,
                                const double limit)
{
    if ( explored_.contains(node) )
        return { MAXFLOAT };

    explored_.add(node);

    if ( node.cost > limit )
        return { node.cost };

    if ( env.goal_test(node.state) ) {
        return { node.cost, Solution(true, explored_, explored_.get(node.state)) };
    }

    double next = MAXFLOAT;
    RBFSResults result;
    Node successor;
    for ( auto& a : env.actions() ) {
        successor = get_child(env, explored_.get(node.state), a);
        successor.cost = successor.state.distance(env.start) + successor.state.distance(env.goal);
        result = ida(env, successor, limit);

        if ( result.solution.success )
            return result;

        next = std::min(next, result.limit);
    }

    return { next };
}


}