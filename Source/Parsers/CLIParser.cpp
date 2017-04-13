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

robo::CLIResults robo::CLIParser::parse(int argc, char** argv)
{
    bin_path_ = sky::Path(argv[0]);

    // Check for correct number of arguments
    if ( argc != 3 ) {
        print_error("Incorrect number of arguments. Expected <filename> and <method> strings");
        return CLIResults();
    }

    // If help flag set, print help, otherwise continue parsing
    if ( strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 ) {
        print_help();
        return CLIResults();
    }

    // Get the filepath as a path relative to the current binary directory
    sky::Path filepath = sky::Path::bin_path(argv);
    filepath.append(argv[1]);

    return CLIResults(filepath.filename().c_str(), filepath.c_str(), argv[2]);
}

void robo::CLIParser::print_error(const char* msg)
{
    printf("%s: %s. See '%s --help'\n",
           bin_path_.filename().c_str(),
           msg,
           bin_path_.filename().c_str());
}

void robo::CLIParser::print_help()
{
    printf("\nusage: %s [-h | --help] <filename> <method>\n\n%s\n",
           bin_path_.filename().c_str(), description_);
}

std::string robo::CLIParser::app_name()
{
    return bin_path_.filename();
}

void robo::CLIParser::set_help_str(const char* help)
{
    help_ = help;
}
