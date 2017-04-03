//
//  IDS.hpp
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


class IDS : public SearchMethod {
public:
    SearchResults search(const Environment& env) override;
protected:
    Node get_child(const Environment& env, Node& parent,
                   const Action action) override;
private:
    /// @brief The frontier used for the search, stored as a LIFO queue
    Frontier<std::vector> frontier_;

    bool depth_limited_search(const Environment& env, SearchResults& results,
                              const unsigned int depth);
};


}



