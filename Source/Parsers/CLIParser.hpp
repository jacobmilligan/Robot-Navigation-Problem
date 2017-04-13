//
//  CLIParser.hpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  13/03/2017
//

#pragma once

#include <Path.hpp>

#include <string>
#include <iostream>

namespace robo {

/// @brief CLIResults holds the results of a parsed cli input.
struct CLIResults {
    CLIResults() {}

    CLIResults(const char* file, const char* path,
               const char* method_used)
        : filename(file), filepath(path), method(method_used)
    {}

    /// @brief The name of the file to search
    std::string filename;

    /// @brief The path to the file
    std::string filepath;

    /// @brief The search method requested
    std::string method;
};

/// @brief CLIParser parses command line input and produces a CLIResults
/// object, printing errors and help messages.
class CLIParser {
public:
    CLIParser(const char* description)
        : description_(description), bin_path_("")
    {}

    void set_help_str(const char* help);

    /// @brief Parses the command line
    /// @param argc Argument count
    /// @param argv Argument string array
    /// @return The CLIResults
    CLIResults parse(int argc, char** argv);

    /// @brief Prints a helpful error to the console in the event that data was
    /// incorrectly input
    /// @param msg The message to print
    void print_error(const char* msg);

    /// @brief Prints a formatted help message to the console
    void print_help();

    /// @brief Gets the applications binary name
    /// @return The binary name
    std::string app_name();
private:
    const char* description_;
    const char* help_;
    sky::Path bin_path_;
};


}