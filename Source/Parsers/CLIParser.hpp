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

#include "Util/PlatformConfig.hpp"

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
        bin_name_ = std::string(argv[0]);
        auto lastslash = bin_name_.rfind(seperator_);

        if ( lastslash != std::string::npos )
            bin_name_.replace(0, lastslash + 1, "");

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

        std::string filepath(argv[0]);
        lastslash = filepath.rfind(seperator_);
        if ( lastslash != std::string::npos )
            filepath.replace(lastslash, filepath.length(), "");

        filepath += seperator_;
        filepath += argv[1];

        return Results { argv[1], filepath, argv[2] };
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
#if ROBONAV_OS_WINDOWS == 1
    static const char seperator_ = '\\';
#else
    static const char seperator_ = '/';
#endif

    std::string desc_;
    std::string bin_name_;
};


}