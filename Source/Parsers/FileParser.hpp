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

#include "Search/Core/Environment.hpp"

#include <vector>
#include <fstream>
#include <sstream>

namespace robo {

/// @brief Enumeration of all valid tokens in a problem file
enum class TokenType {
    /// @brief Grid size
    grid_definition,
    /// @brief The start position
    start_position,
    /// @brief The goal position
    goal_position,
    /// @brief A wall token
    wall,
    /// @brief All other tokens
    unknown
};

/// @brief Token is a tokenized representation of a valid line in a problem
/// file
struct Token {
    TokenType type;

    Token() {}

    Token(const TokenType token_type)
        : type(token_type)
    {}

    /// @brief The tokens associated numeric values (x, y, width, height)
    std::vector<unsigned int> values;
};

/// @brief FileParser parses a problem file and produces an Environment object
/// for searching using a valid search method
class FileParser {
public:
    /// @brief Initializes the file parser and passes in the name of the binary
    /// for use in error messages
    /// @param app_name The binary name
    FileParser(const std::string& app_name)
        : pos_(0), app_name_(app_name), newlines_(0)
    {}

    /// @brief Tokenizes and parses the problem file and produces an
    /// environment object
    /// @param filepath The path of the file to parse
    /// @return The environment object
    Environment parse(const std::string& filepath);

private:
    /// @brief The tokens in the file
    std::vector<Token> tokens_;
    /// @brief The position of the current character being parsed
    int pos_;
    /// @brief The count of newlines encountered
    int newlines_;
    /// @brief The applications name. Used for error messages
    std::string app_name_;

    /// @brief Tokenizes the input ready for parsing
    /// @param env_str The string representation of the contents of the problem
    /// file
    void lex(std::string env_str);

    /// @brief Prints a parsing error to the console
    /// @param type The type of the error that occurred
    /// @param msg The message to display
    void print_error(const std::string& type, const std::string& msg);

    /// @brief Executes the parsing phase
    Environment parse_tokens();

    /// @brief Scans a line until the end of a tuple (wall, goal, start pos etc.)
    /// is encountered, eating all characters along the way
    Token scan_tuple(const std::string& str, TokenType type, char closing_char);

    /// @brief Parses a grid definition token
    /// @param env The environment being built
    /// @param pos Current position in the tokenized input
    /// @return If parsing was successful true, false otherwise
    bool parse_definition(Environment& env, const int pos);

    /// @brief Parses a start position token
    /// @param env The environment being built
    /// @param pos Current position in the tokenized input
    /// @return If parsing was successful true, false otherwise
    bool parse_position(Environment& env, const int pos);

    /// @brief Parses a goal position token
    /// @param env The environment being built
    /// @param pos Current position in the tokenized input
    /// @return If parsing was successful true, false otherwise
    bool parse_goal(Environment& env, const int pos);

    /// @brief Parses a wall token
    /// @param env The environment being built
    /// @param pos Current position in the tokenized input
    /// @return If parsing was successful true, false otherwise
    bool parse_wall(Environment& env, const int pos);
};


}