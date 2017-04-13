//
//  Error.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  13/04/2017
//

#pragma once

#include <cstdio>

namespace robo {


inline void print_visualizer_error(const char* type, const char* msg)
{
    fprintf(stderr, "[robonav visualizer] %s error occurred: %s\n", type, msg);
}


}
