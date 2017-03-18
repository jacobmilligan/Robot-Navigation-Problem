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

#include <Skyrocket/IO/Path.hpp>

#include <string>
#include <iostream>

namespace robo {

struct Results {
    std::string filename;
    std::string filepath;
    std::string method;
};

class CLIParser {
public:
    CLIParser(const std::string& desc)
        : desc_(desc)
    {}

    Results parse(int argc, char** argv)
    {
        bin_name_ = sky::Path(argv[0]).filename();

        if ( argc > 3 || argc <= 1 ) {
            print_error("Incorrect number of arguments");
            return Results();
        }

        for ( int i = 0; i < argc; ++i ) {
            if ( strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0 ) {
                print_help();
                return Results();
            }
        }

        sky::Path filepath = sky::Path::bin_path(argv);
        filepath.append(argv[1]);
        return Results { filepath.filename(), filepath.str(), argv[2] };
    }

    void print_error(const std::string& msg)
    {
        std::cout << bin_name_ << ": " << msg << " see '"
                  << bin_name_ << " --help'" << std::endl;
    }

    void print_help()
    {
        std::cout << "\n";
        std::cout << "usage: " << bin_name_ << " [-h | --help] " << "<filename> <method>\n\n";
        std::cout << desc_ << "\n";
    }

    std::string app_name()
    {
        return bin_name_;
    }
private:
    std::string desc_;
    std::string bin_name_;
};


}