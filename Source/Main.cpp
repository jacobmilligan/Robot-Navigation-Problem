#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"
#include "Visualizer/VisualizerApp.hpp"

int main(int argc, char** argv)
{
    auto methods = robo::generate_method_map();

    std::string description = "Searches for solutions to the Robot Navigation "
        "problem.\nThe following search algorithms are supported for <method>:"
        "\n\n";

    for ( auto& m : methods ) {
        description += "[" + std::string(m.first) + "]\t\t"
                    + m.second->name() + "\n";
    }

    robo::CLIParser cli(description.c_str());

    auto results = cli.parse(argc, argv);
    if ( results.error ) {
        return 1;
    }

    if ( results.method.size() <= 0 ) {
        return 0;
    }

    if ( results.method == "VISUALIZER" ) {
        robo::VisualizerApp app("Robo-visualizer", 1, 32, argv);
        app.run();
        return 0;
    }

    if ( methods.find(results.method) == methods.end() ) {
        auto error = "'" + results.method + "' is not a supported search method";
        cli.print_error(error.c_str());
        return 0;
    }

    robo::FileParser parser(cli.app_name());
    auto& method = *(methods.find(results.method)->second);
    auto env = parser.parse(results.filepath);

    if ( !env.valid() )
        return 0;

    env.step_cost = 1;
    auto path = method.search(env);

    if ( !path.success ) {
        printf("No solution found \n");
    } else {
        printf("%s %s %d %s\n",
               results.filename.c_str(),
               results.method.c_str(),
               path.node_count,
               path.to_string().c_str());
    }

    if ( results.with_stats )
        printf("largest_frontier: %d\n", path.largest_frontier);

    return 0;
}