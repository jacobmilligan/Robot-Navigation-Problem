#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"
#include "Search/SearchMethod.hpp"

void print_output(const std::string& filename, const std::string& method,
                  const unsigned long nodes, const std::vector<robo::Direction>& path)
{
    std::cout << filename << " " << method << " " << nodes << " ";
    for ( auto& d : path ) {
        std::cout << robo::direction_to_string(d) << ";";
    }
}

int main(int argc, char** argv)
{
    std::unordered_map<std::string, std::unique_ptr<robo::SearchMethod>> methods;
    methods["BFS"] = std::make_unique<robo::BreadthFirst>();

    robo::CLIParser cli("Executes several search methods");
    auto results = cli.parse(argc, argv);

    auto method = methods.find(results.method);
    if ( method == methods.end() ) {
        cli.print_error("'" + results.method + "' is not a supported search method");
        return 0;
    }

    robo::FileParser parser(cli.app_name());
    auto env = parser.parse(results.filepath);
    env.step_cost = 1;

    if ( env.valid() ) {
        std::cout << env.to_string() << std::endl;
    }

    auto& path = method->second->search(env);

    print_output(results.filename, results.method, method->second->size(), path);

    return 0;
}