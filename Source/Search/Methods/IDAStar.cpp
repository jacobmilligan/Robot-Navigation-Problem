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
    return astar(env, node, MAXFLOAT).solution;
}

IDAStar::IDAStarResults IDAStar::astar(const Environment& env, const Node& node,
                                       const double limit)
{
    if ( env.goal_test(node.state) )
        return IDAStarResults{ 0, Solution(true, explored_, node) };

    std::vector<Node> successors = {
        get_child(env, node, Action::up),
        get_child(env, node, Action::left),
        get_child(env, node, Action::down),
        get_child(env, node, Action::right)
    };

    if ( successors.empty() )
        return IDAStarResults{ MAXFLOAT, Solution(false, explored_, node) };

    for ( auto& s : successors ) {
        s.cost = std::max(s.cost + env.step_cost, node.cost);
    }

    std::sort(successors.begin(), successors.end(),
              [](const Node& a, const Node& b) {
                  return a.cost < b.cost;
              });

    Node best;
    Node alternative;
    while ( true ) {
        best = successors[0];
        if ( best.cost > limit )
            return IDAStarResults{ best.cost, Solution(false, explored_, best) };

        alternative = successors[1];
        auto result = astar(env, best, std::min(limit, alternative.cost));

        if ( result.solution.success )
            return result;
    }
}


}