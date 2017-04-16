//
//  CLIParser.cpp
//  robonav
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan on 13/04/2017
//  Copyright (c) 2016 Jacob Milligan. All rights reserved.
//

#include "CLIParser.hpp"

namespace robo {


CLIResults CLIParser::parse(int argc, char** argv)
{
    bin_path_ = sky::Path(argv[0]);

    bool with_stats = false;

    for ( int a = 1; a < argc; ++a ) {
        // If help flag set, print help, otherwise continue parsing
        if ( strcmp(argv[a], "--help") == 0 || strcmp(argv[a], "-h") == 0 ) {
            print_help();
            return CLIResults();
        }

        if ( strcmp(argv[a], "--visualizer") == 0 || strcmp(argv[a], "-v") == 0 ) {
            return CLIResults("", "", "VISUALIZER", false);
        }

        if ( strcmp(argv[a], "--stats") == 0 || strcmp(argv[a], "-s") == 0 ) {
            with_stats = true;
        }

    }

    if ( with_stats ) {
        if ( argc != 4 ) {
            print_error("Incorrect number of arguments. "
                            "Expected <filename> and <method> strings");
            return CLIResults();
        }
        if ( strcmp(argv[3], "--stats") != 0 && strcmp(argv[3], "-s") != 0 ) {
            print_error("Invalid option. Option flags must be placed "
                        "after positionals");
            return CLIResults();
        }
    }

    // Check for correct number of arguments
    if ( argc != 3 && !with_stats ) {
        print_error("Incorrect number of arguments. "
                        "Expected <filename> and <method> strings");
        return CLIResults();
    }

    // Get the filepath as a path relative to the current binary directory
    sky::Path filepath = sky::Path::bin_path(argv);
    filepath.append(argv[1]);

    return CLIResults(filepath.filename().c_str(),
                      filepath.c_str(),
                      argv[2],
                      with_stats);
}

void CLIParser::print_error(const char* msg)
{
    printf("%s: %s. See '%s --help'\n",
           bin_path_.filename().c_str(),
           msg,
           bin_path_.filename().c_str());
}

void CLIParser::print_help()
{
    printf("usage: %s %s\n\n%s\nWith the following options supported:\n%s\n",
           bin_path_.filename().c_str(), opts_, description_, flags_);
}

std::string CLIParser::app_name()
{
    return bin_path_.filename();
}


}