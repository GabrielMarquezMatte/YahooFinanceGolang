#include <iostream>
#include <boost/program_options.hpp>
namespace po = boost::program_options;
int main(int argc,char **argv){
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message");
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }
    return 0;
}