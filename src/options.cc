#include <string>

#include "options.h"

namespace claudia {

options::options_description make_options_description()
{
  options::options_description desc("Supported options");

  desc.add_options()                                                                                            //
      ("help,h", "view this help message")                                                                      //
      ("input-file,i", options::value<std::string>()->required(), "diagnostics file generated by -Weverything") //
      ("output-file,o", options::value<std::string>()->required(), "output file for the parsed diagnostics")    //
      ("format,f", options::value<std::string>()->default_value("^(.+):(\\d+):(\\d+): warning: (.+) \\[(.+)\\]$"),
       "diagnostics format: be sure to provide the five needed groups, non-matches are silently ignored"); //

  return desc;
}

options::positional_options_description make_positional_options_description()
{
  options::positional_options_description desc;

  desc.add("input-file", 1);
  desc.add("output-file", 2);

  return desc;
}
}
