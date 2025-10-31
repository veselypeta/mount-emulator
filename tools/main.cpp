#include <Driver/Driver.h>
#include <Target/TargetInfo.h>
#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char *argv[]) {

  po::options_description Desc("Allowed options");
  Desc.add_options()("help", "produce help message")(
      "mount", po::value<std::string>(), "mount model");

  po::variables_map VM;
  po::store(po::parse_command_line(argc, argv, Desc), VM);
  po::notify(VM);

  if (VM.count("help")) {
    std::cout << Desc << '\n';
    return EXIT_FAILURE;
  }

  me::Driver Driver;

  if (!VM.count("mount")) {
    std::cout << "mount model not selected.\n";
    return EXIT_FAILURE;
  }

  // Create the target
  me::Target Target(VM["mount"].as<std::string>());

  // register targets
}
