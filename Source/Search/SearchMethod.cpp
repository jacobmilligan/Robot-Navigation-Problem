//
//  Uninformed.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  14/03/2017
//

#include "Search/SearchMethod.hpp"

namespace robo {

Node SearchMethod::get_child(const Environment& env, Node& parent, const Direction action)
{
    auto state = parent.state;

    switch (action) {
        case Direction::up:
            state.y -= 1;
            break;
        case Direction::left:
            state.x -= 1;
            break;
        case Direction::down:
            state.y += 1;
            break;
        case Direction::right:
            state.x += 1;
            break;
        default: break;
    }

    if ( env.passable(state) )
        return Node(state, &parent, parent.cost + env.step_cost, action);

    return Node(parent.state, nullptr, 1, Direction::unknown);
}

SearchResults SearchMethod::search(const Environment& env)
{
    frontier_clear();
    explored_.clear();

    Node node(env.start, nullptr, 0, Direction::none);
    if ( env.goal_test(env.start) ) {
        return SearchResults(true, explored_.size(), node);
    }

    frontier_add(node);
    explored_[node.state] = node;
    operations_.push_back(node);

    Node child;
    double parent_cost = 0.0;
    while ( !frontier_empty() ) {
        node = frontier_remove();

        for ( auto& a : env.actions() ) {
            child = get_child(env, explored_[node.state], a);
            if ( explored_.find(child.state) == explored_.end() ) {
                explored_[child.state] = child;
                operations_.push_back(child);
                if ( env.goal_test(child.state) ) {
                    return SearchResults(true, explored_.size(), child);
                }

                frontier_add(child);
            }
        }
    }

    return SearchResults(false, explored_.size(), child);
}


}