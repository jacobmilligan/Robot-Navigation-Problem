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

    RBFSResults results;
    results.limit = node.state.distance(env.goal, dist_func_);
    while ( !results.solution.success && results.limit < infinity_ ) {
        explored_.clear();
        results = ida(env, node, results.limit);
    }

    return results.solution;
}

IDAStar::RBFSResults IDAStar::ida(const Environment& env, const Node& node,
                                const double limit)
{
    if ( explored_.contains(node) )
        return { infinity_ };

    if ( node.cost > limit )
        return { node.cost };

    explored_.append(node);

    if ( env.goal_test(node.state) )
        return { node.cost, Solution(true, explored_, &node) };

    Node successor;
    for ( auto& a : env.actions() ) {
        successor = get_child(env, &node, a);
        successor.cost = node.cost + successor.state.distance(env.goal, dist_func_);
        frontier_.add(successor);
    }

    double next = infinity_;
    RBFSResults result;
    while ( !frontier_.empty() ) {
        successor = frontier_.remove();
        result = ida(env, successor, limit);

        if ( result.solution.success )
            return result;

        next = std::min(next, result.limit);
    }

    return { next };
}


}