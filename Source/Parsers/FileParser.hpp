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

#include <vector>
#include <fstream>
#include <sstream>

namespace robo {


struct Environment {
    Environment()
        : valid_(false)
    {}

    Environment(int cols, int rows)
        : valid_(true)
    {
        grid_.resize(rows);
        for ( auto& row : grid_ ) {
            row.resize(cols);
        }
    }

    void set_value(int col, int row, int value)
    {
        grid_[row][col] = value;
    }

    std::string to_string()
    {
        std::stringstream ss;
        for ( auto& c : grid_ ) {
            for ( auto& r : c ) {
                ss << r << " ";
            }
            ss << "\n";
        }
        return ss.str();
    }

    bool valid()
    {
        return valid_;
    }

private:
    bool valid_;
    std::vector<std::vector<int>> grid_;

};

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

    std::vector<int> values;
};

class FileParser {
public:
    FileParser(const std::string& app_name)
        : pos_(0), app_name_(app_name)
    {}

    Environment parse(const std::string& filepath)
    {
        std::ifstream file(filepath);

        if ( !file ) {
            print_error("Parse", "No such file found with the specified name");
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