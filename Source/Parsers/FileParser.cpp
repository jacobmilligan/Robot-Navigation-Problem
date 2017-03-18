//
//  Parsers.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  13/03/2017
//

#include "FileParser.hpp"

namespace robo {


void FileParser::lex(std::string env_str)
{
    pos_ = 0;
    int newlines = 0;
    char cur = env_str[pos_];
    Token tok;

    while (pos_ < env_str.size()) {
        switch (cur) {
            case '[':
                tok = scan_tuple(env_str, TokenType::grid_definition, ']');
                tokens_.push_back(tok);
                newlines++;
                break;
            case '(':
                tok = scan_tuple(env_str, TokenType::wall, ')');
                if ( tok.values.size() < 3 ) {
                    if ( newlines == 1 )
                        tok.type = TokenType::start_position;
                    if ( newlines == 2 )
                        tok.type = TokenType::goal_position;
                    if ( newlines > 2 )
                        tok.type = TokenType::unknown;
                }
                tokens_.push_back(tok);
                newlines++;
                break;
        }
        pos_++;
        cur = env_str[pos_];
    }
}

Token FileParser::scan_tuple(const std::string& str, TokenType type, char closing_char)
{
    auto tok = Token(type);
    std::string value;
    char cur = ' ';

    while ( cur != closing_char && pos_ < str.size() ) {
        cur = str[pos_++];

        switch (cur) {
            case '\n':
                pos_++;
                return Token(TokenType::unknown);
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                value = "";
                for (;;) {
                    if ( !isdigit(cur) )
                        break;
                    value += cur;
                    cur = str[pos_++];
                }
                tok.values.push_back(std::stoi(value));
                break;
            case ',':
            case ' ':
                break;
        }
    }

    return tok;
}

Environment FileParser::parse_tokens()
{
    int pos = 0;
    bool valid = true;

    Environment env(0, 0);

    for ( int t = 0; t < tokens_.size(); ++t ) {
        if ( !valid )
            break;

        switch (tokens_[t].type) {
            case TokenType::grid_definition:
                valid = parse_definition(env, t);
                break;
            case TokenType::start_position:
                valid = parse_position(env, t);
                break;
            case TokenType::goal_position:
                valid = parse_goal(env, t);
                break;
            case TokenType::wall:
                valid = parse_wall(env, t);
                break;
            case TokenType::unknown:
                std::string msg("Syntax error at line ");
                msg += t;
                print_error("Parse", msg);
                valid = false;
                break;
        }
    }

    if (!valid)
        return Environment();

    return env;
}

void FileParser::print_error(const std::string& type, const std::string& msg)
{
    std::stringstream ss;
    ss << app_name_ << ": " << type << " error: " << msg;
    printf("%s\n", ss.str().c_str());
}

bool FileParser::parse_definition(Environment& env, const int pos)
{
    if ( pos != 0 ) {
        print_error("Parse", "Line 1 must be a grid size in the form [N,M]");
        return false;
    }

    auto& tok = tokens_[pos];
    auto rows = tok.values[0];
    auto cols = tok.values[1];

    env = Environment(cols, rows);

    return true;
}

bool FileParser::parse_position(Environment& env, const int pos)
{
    if ( pos != 1 ) {
        print_error("Parse", "Line 2 must be a starting position in the form (x,y)");
        return false;
    }

    auto& tok = tokens_[pos];
    auto col = tok.values[0];
    auto row = tok.values[1];

    env[row][col] = Cell::start;
    env.start = Point(col, row);

    return true;
}

bool FileParser::parse_goal(Environment& env, const int pos)
{
    if ( pos != 2 ) {
        print_error("Parse", "Line 3 must be a goal position in the form (x,y)");
        return false;
    }

    auto& tok = tokens_[pos];
    auto col = tok.values[0];
    auto row = tok.values[1];

    env[row][col] = Cell::goal;
    env.goal = Point(col, row);

    return true;
}

bool FileParser::parse_wall(Environment& env, const int pos)
{
    if ( pos < 3 ) {
        std::string msg("Expected a wall definition at line ");
        msg += pos;
        print_error("Parse", msg);
        return false;
    }

    auto& tok = tokens_[pos];
    auto row = tok.values[1];
    auto col = tok.values[0];
    auto width = tok.values[2];
    auto height = tok.values[3];

    for ( int i = 0; i < height; ++i ) {
        for ( int j = 0; j < width; ++j ) {
            env[row + i][col + j] = Cell::wall;
        }
    }

    return true;
}


}
