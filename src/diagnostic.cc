#include <vector>
#include <utility>
#include <tuple>

#include "diagnostic.h"

namespace claudia {

diagnostic::diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag)
    : file{std::move(file)}, line{line}, column{column}, message{std::move(message)}, flag{std::move(flag)}
{
}

property::ptree diagnostic::report() const
{
  property::ptree root;

  const std::vector<std::pair<std::string, std::string>> description{ //
      {"filename", file},                                             //
      {"line", std::to_string(line)},                                 //
      {"column", std::to_string(column)},                             //
      {"message", message},                                           //
      {"flag", flag}                                                  //
  };

  for (const auto kv : description)
    root.push_back(property::ptree::value_type(kv.first, property::ptree(kv.second)));

  return root;
}

bool operator<(const diagnostic& lhs, const diagnostic& rhs)
{
  return std::tie(lhs.file, lhs.line, lhs.column, lhs.message, lhs.flag) <
         std::tie(rhs.file, rhs.line, rhs.column, rhs.message, rhs.flag);
}

bool operator==(const diagnostic& lhs, const diagnostic& rhs)
{
  return std::tie(lhs.file, lhs.line, lhs.column, lhs.message, lhs.flag) ==
         std::tie(rhs.file, rhs.line, rhs.column, rhs.message, rhs.flag);
}
}
