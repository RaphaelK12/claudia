#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

#include "option.h"
#include "parser.h"

int main(int argc, char** argv) try
{
  detail::option opt{argc, argv, "diagnostics.txt"};

  if (!opt.require(1))
    return opt.abort("diagnostics file expected");


  std::ifstream in{opt.get<std::string>(0)};

  if (!in)
    return opt.abort("bad diagnostics file");


  detail::parser par{in};

  /* XXX: just print it for now.. */
  std::cout << par;
}
catch (const std::exception& e)
{
  std::cerr << e.what() << '\n';
}
