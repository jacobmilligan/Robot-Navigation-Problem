//
//  IterativeDeepeningSearch.hpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 3/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#pragma once


#include "Search/Core/SearchMethod.hpp"

namespace robo {


class IterativeDeepeningSearch : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
    ExploredSet& explored() override;
protected:
    Node get_child(const Environment& env, Node& parent,
                   const Action action) override;
private:
    /// @brief The frontier used for the search, stored as a LIFO queue
    Frontier<std::vector> frontier_;
};


}



