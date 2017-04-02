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

    CLIResults(const std::string &file, const std::string &path,
               const std::string &method_used)
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
    CLIParser(const std::string& description)
        : description_(description)
    {}

    /// @brief Parses the command line
    /// @param argc Argument count
    /// @param argv Argument string array
    /// @return The CLIResults
    CLIResults parse(int argc, char** argv)
    {
        bin_name_ = sky::Path(argv[0]).filename();

        // If help flag set, print help, otherwise continue parsing
        if ( strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 ) {
            print_help();
            return CLIResults();
        }

        // Check for correct number of arguments
        if ( argc != 3 ) {
            print_error("Incorrect number of arguments");
            return CLIResults();
        }

        // Get the filepath as a path relative to the current binary directory
        sky::Path filepath = sky::Path::bin_path(argv);
        filepath.append(argv[1]);

        return CLIResults(filepath.filename(), filepath.str(), argv[2]);
    }

    /// @brief Prints a helpful error to the console in the event that data was
    /// incorrectly input
    /// @param msg The message to print
    void print_error(const std::string& msg)
    {
        std::cout << bin_name_ << ": " << msg << " see '"
                  << bin_name_ << " --help'" << std::endl;
    }

    /// @brief Prints a formatted help message to the console
    void print_help()
    {
        std::cout << "\n";
        std::cout << "usage: " << bin_name_ << " [-h | --help] " << "<filename> <method>\n\n";
        std::cout << description_ << "\n";
    }

    /// @brief Gets the applications binary name
    /// @return The binary name
    std::string app_name()
    {
        return bin_name_;
    }
private:
    std::string description_;
    std::string bin_name_;
};


}