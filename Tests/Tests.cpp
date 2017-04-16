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

#include "Search/Core/SearchMethod.hpp"
#include "Parsers/FileParser.hpp"

#include "Search/Methods/BreadthFirst.hpp"
#include "Search/Methods/DepthFirst.hpp"
#include "Search/Methods/GreedyBestFirst.hpp"
#include "Search/Methods/AStar.hpp"

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <Path.hpp>

#include <random>

struct SearchTestCase {
    std::string file;
    int expected_length;
};

class SearchTestsFixture {
public:
    static sky::Path root_;

    SearchTestsFixture()
        : methods_(robo::generate_method_map()),
          parser_("SearchTests")
    {}

protected:
    robo::MethodMap methods_;
    robo::FileParser parser_;

    std::vector<SearchTestCase> test_cases_;
};

sky::Path SearchTestsFixture::root_ = "";

void print_environment(const robo::Environment& env)
{
    char cellchar;
    for ( unsigned long x = 0; x < env.size().x; ++x ) {
        for ( unsigned long y = 0; y < env.size().y; ++y ) {
            switch (env[x][y]) {
                case robo::Cell::empty:
                    cellchar = '.';
                    break;
                case robo::Cell::start:
                    cellchar = 'O';
                    break;
                case robo::Cell::goal:
                    cellchar = 'X';
                    break;
                case robo::Cell::wall:
                    cellchar = '*';
                    break;
            }

            printf("%c", cellchar);
        }

        printf("\n");
    }
}

int main(int argc, char** argv)
{
    SearchTestsFixture::root_.assign(sky::Path::bin_path(argv));
    SearchTestsFixture::root_.append("../Tests");



    int result = Catch::Session().run(argc, argv);

    return ( result < 0xff ? result : 0xff );
}

TEST_CASE_METHOD(SearchTestsFixture,
                 "Search methods fail when goal can't be found", "[failure]")
{
    auto env = parser_.parse(root_.get_relative("failure.txt"));
    robo::Solution solution;

    for ( auto& m : methods_ ) {
        solution = m.second->search(env);
        REQUIRE_FALSE(solution.success);
    }
}

TEST_CASE_METHOD(SearchTestsFixture, "A* is optimal",
                 "[as]")
{
    test_cases_ = {
        { root_.get_relative("test1.txt"), 12 },
        { root_.get_relative("test2.txt"), 53 },
        { root_.get_relative("test3.txt"), 1599 },
        { root_.get_relative("test4.txt"), 1988 },
        { root_.get_relative("test5.txt"), 1998 },
        { root_.get_relative("test6.txt"), 1998 },
    };

    auto env = parser_.parse(test_cases_[4].file);
    print_environment(env);

    robo::Solution solution;
    for ( auto& t : test_cases_ ) {
        auto env = parser_.parse(t.file);
        REQUIRE( (env.size().x > 0 && env.size().y > 0) );
        solution = methods_["AS"]->search(env);
        REQUIRE(solution.success);
        REQUIRE(solution.path.size() == t.expected_length);
    }
}

TEST_CASE_METHOD(SearchTestsFixture, "IDS Search", "[ids]")
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(0, 63);
    for ( int i = 0; i < 10; ++i ) {
        robo::Environment env(64, 64);
        env.start = robo::Point(dist(engine), dist(engine));
        env.goal = robo::Point(dist(engine), dist(engine));
        auto lim = dist(engine);

        for ( int j = 0; j < lim; ++j ) {
            auto point = robo::Point(dist(engine), dist(engine));
            if ( env[point.x][point.y] == robo::Cell::empty ) {
                env.set_cell(point.x, point.y, robo::Cell::wall);
            }
        }

        auto expected = methods_["AS"]->search(env);
        auto actual = methods_["IDS"]->search(env);

        SECTION("IDS is complete")
        {
            REQUIRE(expected.success == actual.success);
        }

        SECTION("IDS is optimal")
        {
            if ( expected.success )
                REQUIRE(expected.path.size() == actual.path.size());
        }
    }
}

TEST_CASE_METHOD(SearchTestsFixture, "IDA* Search", "[ida]")
{
    std::random_device seeder;
    std::mt19937 engine(seeder());
    std::uniform_int_distribution<int> dist(0, 31);
    for ( int i = 0; i < 10; ++i ) {
        robo::Environment env(32, 32);
        env.start = robo::Point(dist(engine), dist(engine));
        env.goal = robo::Point(dist(engine), dist(engine));
        auto lim = dist(engine);

        for ( int j = 0; j < lim; ++j ) {
            auto point = robo::Point(dist(engine), dist(engine));
            if ( env[point.x][point.y] == robo::Cell::empty ) {
                env.set_cell(point.x, point.y, robo::Cell::wall);
            }
        }

        auto expected = methods_["AS"]->search(env);
        auto actual = methods_["IDAS"]->search(env);

        SECTION("IDA* is complete")
        {
            REQUIRE(expected.success == actual.success);
        }

        SECTION("IDA* is optimal")
        {
            if ( expected.success )
                REQUIRE(expected.path.size() == actual.path.size());
        }
    }
}

