//
//  UninformaedTests.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  16/03/2017
//

#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "Containers/Graph.hpp"
#include "Parsers/FileParser.hpp"

#include <array>
#include <Search/Uninformed.hpp>

TEST_CASE("uninformed tests", "[uninformed]")
{
    robo::FileParser parser("Tests");
    auto env = parser.parse(
        "/Users/Jacob/Uni/IntroAI/Assignment1/cmake-build-debug/test.txt"
    );

    // Reverse direction
    std::array<robo::Direction, 12> path = {
        robo::Direction::right,
        robo::Direction::down,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::right,
        robo::Direction::down,
    };

    robo::BreadthFirst bfs;
    auto& test = bfs.search(env);

    SECTION("bfs chooses accurate path")
    {
        for ( int i = 0; i < test.size(); ++i ) {
            REQUIRE(test[i] == path[i]);
        }
    }
}