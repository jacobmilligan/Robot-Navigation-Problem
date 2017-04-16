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
};

sky::Path SearchTestsFixture::root_ = "";

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