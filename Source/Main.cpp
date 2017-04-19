//
//  AStar.cpp
//  COS30019 Intro To AI - Assignment 1
//  Robot Navigation
//
//  --------------------------------------------------------------
//
//  Created by
//  Jacob Milligan 100660682
//  19/03/2017
//

#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"
#include "Visualizer/VisualizerApp.hpp"

int main(int argc, char** argv)
{
    // Create search method map
    auto methods = robo::generate_method_map();

    // Generate the command line description used for the -h flag

    std::string description = "Searches for solutions to the Robot Navigation "
        "problem.\nThe following search algorithms are supported for <method>:"
        "\n\n";

    for ( auto& m : methods ) {
        description += "[" + std::string(m.first) + "]\t\t"
                    + m.second->name() + "\n";
    }

    // Parse the command line and check for an error in input
    robo::CLIParser cli(description.c_str());
    auto results = cli.parse(argc, argv);
    if ( results.error ) {
        return 1;
    }

    // Checks if the search method string was entered
    if ( results.method.size() <= 0 ) {
        return 0;
    }

    // Check if the -v flag was used (returning VISUALIZER as method) and launch
    // the visualizer instead of the command line app
    if ( results.method == "VISUALIZER" ) {
        robo::VisualizerApp app("Robo-visualizer", 1, 32, argv);
        app.run();
        return 0;
    }

    // Check for valid search method
    if ( methods.find(results.method) == methods.end() ) {
        auto error = "'" + results.method + "' is not a supported search method";
        cli.print_error(error.c_str());
        return 0;
    }

    // Parse the specified file and generate a search environment
    robo::FileParser parser(cli.app_name());
    auto& method = *(methods.find(results.method)->second);
    auto env = parser.parse(results.filepath);

    // Exit if the file input was bad
    if ( !env.valid() )
        return 0;

    // Set step cost to a uniform 1 as according to the assignment spec
    env.step_cost = 1;
    auto path = method.search(env); // execute search using the specified search method

    // Check if the path was successful and print results if so, otherwise print
    // "No solution found"
    if ( !path.success ) {
        printf("No solution found \n");
    } else {
        printf("%s %s %d %s\n",
               results.filename.c_str(),
               results.method.c_str(),
               path.node_count,
               path.to_string().c_str());
    }

    // If the -s flag was used, print the largest frontier
    if ( results.with_stats )
        printf("largest_frontier: %d\n", path.largest_frontier);

    return 0;
}