#include "Parsers/CLIParser.hpp"
#include "Parsers/FileParser.hpp"

int main(int argc, char** argv)
{
    robo::CLIParser cli("Executes several search methods");
    auto results = cli.parse(argc, argv);

    robo::FileParser parser(cli.app_name());
    auto env = parser.parse(results.filepath);

    if ( env.valid() ) {
        printf("%s\n", env.to_string().c_str());
    }

    return 0;
}