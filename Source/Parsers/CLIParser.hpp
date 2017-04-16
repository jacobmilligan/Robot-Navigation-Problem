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
    CLIResults()
        : with_stats(false), error(true)
    {}

    CLIResults(const char* file, const char* path,
               const char* method_used, const bool stats)
        : filename(file),
          filepath(path),
          method(method_used),
          with_stats(stats),
          error(false)
    {}

    /// @brief The name of the file to search
    std::string filename;

    /// @brief The path to the file
    std::string filepath;

    /// @brief The search method requested
    std::string method;

    bool with_stats;

    bool error;
};

/// @brief CLIParser parses command line input and produces a CLIResults
/// object, printing errors and help messages.
class CLIParser {
public:
    CLIParser(const char* description)
        : description_(description), bin_path_("")
    {}

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

    const char* opts_ =     "[-h | --help] [-v | --visualizer] [-s | --stats] <filename> <method>";

    const char* flags_ =    "-h, --help      \t\tPrints help information\n"
                            "-v, --visualizer\t\tRuns the interactive visualizer instead, showing "
                                                "changes in the search tree\n"
                            "-s, --stats     \t\tOutput statistics about the method executed alongside normal output\n";
    sky::Path bin_path_;
};


}