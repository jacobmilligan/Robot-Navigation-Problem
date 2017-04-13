//
//  SearchMethod.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  14/03/2017
//

#include "SearchMethod.hpp"

#include "Search/Methods/BreadthFirst.hpp"
#include "Search/Methods/DepthFirst.hpp"
#include "Search/Methods/GreedyBestFirst.hpp"
#include "Search/Methods/AStar.hpp"
#include "Search/Methods/IDS.hpp"
#include "Search/Methods/IDAStar.hpp"

namespace robo {

Node SearchMethod::get_child(const Environment& env, const Node* parent, const Action action)
{
    auto state = parent->state;

    switch (action) {
        case Action::up:
            state.y -= 1;
            break;
        case Action::left:
            state.x -= 1;
            break;
        case Action::down:
            state.y += 1;
            break;
        case Action::right:
            state.x += 1;
            break;
        default: break;
    }
    auto passable = env.passable(state);
    if ( passable )
        return Node(state, parent, parent->cost + env.step_cost, action);

    return Node(parent->state, nullptr, 1, Action::unknown);
}

Solution::Solution(const bool is_succesful, const ExploredSet& explored, const Node* end)
    : success(is_succesful), node_count(explored.size())
{
    path.clear();
    auto* node = end->parent_ptr;
    while ( node->parent_ptr != nullptr ) {
        path.push_back(*node);
        node = node->parent_ptr;
    }
    std::reverse(path.begin(), path.end());
}

std::string Solution::to_string()
{
    std::string output = "";
    for ( auto& d : path ) {
        output += robo::direction_to_string(d.action) + "; ";
    }
    return output;
}

MethodMap generate_method_map()
{
    MethodMap methods;

    methods["BFS"] = std::make_unique<robo::BreadthFirst>();
    methods["DFS"] = std::make_unique<robo::DepthFirst>();
    methods["GBFS"] = std::make_unique<robo::GreedyBestFirst>();
    methods["AS"] = std::make_unique<robo::AStar>();
    methods["IDS"] = std::make_unique<robo::IDS>();
    methods["IDAS"] = std::make_unique<robo::IDAStar>();

    return methods;
}

}