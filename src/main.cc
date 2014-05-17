#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "option.h"
#include "parser.h"

int main(int argc, char** argv) try
{
  detail::option opt{argc, argv, "diagnostics.txt [ --csv | --json ]"};

  if (!opt.require(1))
    return opt.abort("diagnostics file expected");


  std::ifstream in{opt.get<std::string>(0)};

  if (!in)
    return opt.abort("bad diagnostics file");


  detail::parser par{in};

  if (opt.require(2) && opt.get<std::string>(1) == "--csv")
    std::cout << par.csv();
  else /* json by default */
    std::cout << par.json();
}
catch (const std::exception& e)
{
  std::cerr << e.what() << '\n';
}
