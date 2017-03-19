//
//  Parsers.hpp
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

#include "Search/Environment.hpp"

#include <vector>
#include <fstream>
#include <sstream>

namespace robo {

enum class TokenType {
    grid_definition,
    start_position,
    goal_position,
    wall,
    unknown
};

struct Token {
    TokenType type;

    Token() {}

    Token(const TokenType token_type)
        : type(token_type)
    {}

    std::vector<unsigned int> values;
};

class FileParser {
public:
    FileParser(const std::string& app_name)
        : pos_(0), app_name_(app_name), newlines_(0)
    {}

    Environment parse(const std::string& filepath)
    {
        std::ifstream file(filepath);

        if ( !file ) {
            print_error("File parsing", "No such file found with the specified name");
            return Environment();
        }

        std::stringstream ss;
        ss << file.rdbuf();
        file.close();

        lex(ss.str());
        return parse_tokens();
    }

private:
    std::vector<Token> tokens_;
    int pos_;
    int newlines_;
    std::string app_name_;

    void print_error(const std::string& type, const std::string& msg);
    void lex(std::string env_str);
    Environment parse_tokens();
    Token scan_tuple(const std::string& str, TokenType type, char closing_char);

    bool parse_definition(Environment& env, const int pos);
    bool parse_position(Environment& env, const int pos);
    bool parse_goal(Environment& env, const int pos);
    bool parse_wall(Environment& env, const int pos);
};


}