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

    IDAResults results;
    results.limit = node.state.distance(env.goal, dist_func_);
    // Run iterations of IDA* until solution found
    while ( !results.solution.success && results.limit < infinity_ ) {
        explored_.clear();
        results = ida(env, node, results.limit * 2); // use limit * 2 to speed up search
    }

    return results.solution;
}

IDAStar::IDAResults IDAStar::ida(const Environment& env, const Node& node,
                                  const double limit)
{
    // Check for cutoff
    if ( node.cost > limit )
        return { node.cost };

    explored_.overwrite(node);

    if ( env.goal_test(node.state) )
        return { node.cost, Solution(true, explored_, &node, frontier_.largest_size()) };

    Node successor;
    for ( auto& a : env.actions() ) {
        successor = get_child(env, &node, a);
        successor.cost = node.cost + successor.state.distance(env.goal, dist_func_);

        // Check if already in existing path, if not add to current frontier
        if ( tentative_.find(successor.state) == tentative_.end() ) {
            frontier_.add(successor);
            tentative_[successor.state] = true;
        }
    }


    double next = infinity_;
    IDAResults result;
    // Check all children
    while ( !frontier_.empty() ) {
        successor = frontier_.remove();
        tentative_.erase(successor.state);

        if ( explored_.contains(successor) )
            continue;

        result = ida(env, successor, limit);

        if ( result.solution.success )
            return result;

        next = std::min(next, result.limit);
    }

    return { next };
}


}