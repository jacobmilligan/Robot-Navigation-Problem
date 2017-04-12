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
    auto node = Node(env.start, nullptr, 0, Action::none);
    node.cost = node.state.distance(env.goal, dist_func_);

    RBFSResults results;
    results.limit = node.state.distance(env.goal, dist_func_);
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

    if ( node.cost > limit ) {
        return {node.cost};
    }

    if ( env.goal_test(node.state) ) {
        return { node.cost, Solution(true, explored_, &node) };
    }

    explored_.add(node);

    double next = MAXFLOAT;
    RBFSResults result;
    Node successor;
    for ( auto& a : env.actions() ) {
        successor = get_child(env, &node, a);
        successor.cost = node.cost + successor.state.distance(env.goal, dist_func_);
        result = ida(env, successor, limit);

        if ( result.solution.success )
            return result;

        next = std::min(next, result.limit);
    }

    return { next };
}


}