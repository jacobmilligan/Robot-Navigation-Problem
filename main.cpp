#include <Visualizer/VisualizerApp.hpp>
#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"
#include "Search/SearchMethod.hpp"
#include "Visualizer/VisualizerApp.hpp"

using MethodMap = std::unordered_map<std::string, std::unique_ptr<robo::SearchMethod>>;

void populate_search_methods(MethodMap& methods)
{
    methods["BFS"] = std::make_unique<robo::BreadthFirst>();
    methods["DFS"] = std::make_unique<robo::DepthFirst>();
    methods["GBFS"] = std::make_unique<robo::GreedyBestFirst>();
}

void print_output(const std::string& filename, const std::string& method,
                  const robo::SearchResults& results)
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
    robo::FileParser parser(cli.app_name());

    populate_search_methods(methods);

    auto results = cli.parse(argc, argv);
    if ( methods.find(results.method) == methods.end() ) {
        cli.print_error("'" + results.method + "' is not a supported search method");
        return 0;
    }

    auto& method = *methods.find(results.method)->second;
    auto env = parser.parse(results.filepath);
    env.step_cost = 1;
    auto path = method.search(env);

    print_output(results.filename, results.method, path);

    robo::VisualizerApp app(cli.app_name(), env, method.explored(), path);
    app.set_speed(3);
    app.set_tilesize(80);
    app.run();

    return 0;
}