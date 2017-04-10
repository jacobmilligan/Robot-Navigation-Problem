#include <Search/Methods/IDS.hpp>
#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"
#include "Visualizer/VisualizerApp.hpp"

#include "Search/Methods/BreadthFirst.hpp"
#include "Search/Methods/DepthFirst.hpp"
#include "Search/Methods/GreedyBestFirst.hpp"
#include "Search/Methods/AStar.hpp"

using MethodMap = std::unordered_map<std::string, std::unique_ptr<robo::SearchMethod>>;

void populate_search_methods(MethodMap& methods)
{
    methods["BFS"] = std::make_unique<robo::BreadthFirst>();
    methods["DFS"] = std::make_unique<robo::DepthFirst>();
    methods["GBFS"] = std::make_unique<robo::GreedyBestFirst>();
    methods["AS"] = std::make_unique<robo::AStar>();
    methods["IDS"] = std::make_unique<robo::IDS>();
}

void print_output(const std::string& filename, const std::string& method,
                  const robo::Solution& results)
{
    std::cout << filename << " " << method << " " << results.node_count << " ";
    for ( auto& d : results.path ) {
        std::cout << robo::direction_to_string(d.action) << ";";
    }
}

int main(int argc, char** argv)
{
    MethodMap methods;
    robo::CLIParser cli("Executes several search methods");

    populate_search_methods(methods);

    auto results = cli.parse(argc, argv);
    if ( results.method.size() <= 0 ) {
        return 0;
    }

    if ( methods.find(results.method) == methods.end() ) {
        cli.print_error("'" + results.method + "' is not a supported search method");
        return 0;
    }

    robo::FileParser parser(cli.app_name());
    auto& method = *methods.find(results.method)->second;
    auto env = parser.parse(results.filepath);

    if ( !env.valid() ) {
        return 0;
    }

    env.step_cost = 1;
    auto path = method.search(env);

    print_output(results.filename, results.method, path);

    return 0;
}