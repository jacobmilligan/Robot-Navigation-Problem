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
#include "Search/SearchMethod.hpp"
#include "Parsers/FileParser.hpp"


TEST_CASE("uninformed search methods execute correctly", "[uninformed]")
{
    //================================
    //      Setup test case
    //================================
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
    robo::DepthFirst dfs;

    //================================
    //      BFS Tests
    //================================
    SECTION("breadth first search")
    {
        auto results = bfs.search(env);

        SECTION("bfs has correct path length")
        {
            REQUIRE(results.node_count > 1);
            REQUIRE(results.path.size() == path.size());
        }

        SECTION("bfs has correct path")
        {
            for ( int i = 0; i < path.size(); ++i ) {
                REQUIRE(results.path[i] == path[i]);
            }
        }
    }

    //================================
    //      DFS Tests
    //================================
    SECTION("depth first search")
    {
        auto results = dfs.search(env);

        SECTION("dfs has correct path length")
        {
            REQUIRE(results.node_count > 1);
            REQUIRE(results.path.size() == path.size());
        }

        SECTION("dfs has correct path")
        {
            for ( int i = 0; i < path.size(); ++i ) {
                REQUIRE(results.path[i] == path[i]);
            }
        }
    }
}