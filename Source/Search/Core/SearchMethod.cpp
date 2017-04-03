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

namespace robo {

Node SearchMethod::get_child(const Environment& env, Node& parent, const Action action)
{
    auto state = parent.state;

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

    if ( env.passable(state) )
        return Node(state, parent.id, parent.cost + env.step_cost, action);

    return Node(parent.state, -1, 1, Action::unknown);
}

}