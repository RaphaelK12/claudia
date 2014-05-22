#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "options.h"
#include "parser.h"

using namespace claudia;

int main(int argc, char** argv) try
{
  const auto desc = make_options_description();
  const auto pos = make_positional_options_description();

  options::command_line_parser cmd(argc, argv);
  cmd.options(desc);
  cmd.positional(pos);

  options::variables_map variables;
  options::store(cmd.run(), variables);

  if (variables.count("help")) {
    std::cout << "Usage: " << argv[0] << " input-file output-file\n";
    std::cout << desc;
    return EXIT_SUCCESS;
  }

  options::notify(variables);

  const auto infile = variables["input-file"].as<std::string>();
  const auto outfile = variables["output-file"].as<std::string>();

  std::ifstream in{infile};
  if (!in)
    throw std::runtime_error{"bad input-file"};

  std::ofstream out{outfile};
  if (!out)
    throw std::runtime_error{"bad outut-file"};

  const auto fmt = variables["format"].as<std::string>();

  parser parser{in, fmt};
  parser.report(out);
}
catch (const std::exception& e)
{
  std::cerr << "Error: " << e.what() << '\n';
  return EXIT_FAILURE;
}
