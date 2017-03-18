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

    const int min_path = 12;

    // Reverse direction
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
            REQUIRE(results.path.size() == min_path);
        }

        SECTION("bfs has correct path")
        {
            robo::Point state = results.path[min_path - 1].state;
            REQUIRE(state == env.goal);
            for ( int i = 0; i < min_path; ++i ) {
                state = results.path[i].state;
                REQUIRE(env.get_cell(state) != robo::Cell::wall);
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
            REQUIRE(results.path.size() == min_path);
        }

        SECTION("dfs has correct path")
        {
            robo::Point state = results.path[min_path - 1].state;
            REQUIRE(state == env.goal);
            for ( int i = 0; i < min_path; ++i ) {
                state = results.path[i].state;
                REQUIRE(env.get_cell(state) != robo::Cell::wall);
            }
        }
    }
}


TEST_CASE("informed search methods execute correctly", "[informed]")
{
    //================================
    //      Setup test case
    //================================
    robo::FileParser parser("Tests");
    auto env = parser.parse(
        "/Users/Jacob/Uni/IntroAI/Assignment1/cmake-build-debug/test.txt"
    );

    const int min_path = 12;

    // Reverse direction
    robo::GreedyBestFirst gbfs;

    //================================
    //      BFS Tests
    //================================
    SECTION("greedy best first search")
    {
        auto results = gbfs.search(env);

        SECTION("gbfs has correct path length")
        {
            REQUIRE(results.node_count > 1);
            REQUIRE(results.node_count == 29);
            REQUIRE(results.path.size() == min_path);
        }

        SECTION("gbfs has correct path")
        {
            robo::Point state = results.path[min_path - 1].state;
            REQUIRE(state == env.goal);
            for ( int i = 0; i < min_path; ++i ) {
                state = results.path[i].state;
                REQUIRE(env.get_cell(state) != robo::Cell::wall);
            }
        }
    }
}