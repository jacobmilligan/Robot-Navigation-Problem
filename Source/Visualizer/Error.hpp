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

/// @brief Prints a formatted error message to the console for the visualizer
/// @param type The type of error message that occurred
/// @param msg The message to print
inline void print_visualizer_error(const char* type, const char* msg)
{
    fprintf(stderr, "[search visualizer] %s error occurred: %s\n", type, msg);
}


}
