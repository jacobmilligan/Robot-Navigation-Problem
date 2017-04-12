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
    Solution search(const Environment& env) override;
private:
    /// @brief The frontier used for the search, stored as a LIFO queue
    Frontier<std::vector> frontier_;

    struct IDSResults {
        Solution solution;
        bool cutoff;
    };

    IDSResults depth_limited_search(const Environment& env, const unsigned int limit);

    IDSResults recursive_dls(const Node& node, const Environment& env,
                             const int depth);
};


}



