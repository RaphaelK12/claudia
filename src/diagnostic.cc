#include <utility>
#include <vector>
#include <utility>
#include <tuple>

#include "diagnostic.h"

namespace claudia {

diagnostic::diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag)
    : file_{std::move(file)}, line_{line}, column_{column}, message_{std::move(message)}, flag_{std::move(flag)}
{
}

boost::property_tree::ptree diagnostic::report() const
{
  boost::property_tree::ptree root;

  const std::vector<std::pair<std::string, std::string>> description{ //
      {"filename", file_},                                            //
      {"line", std::to_string(line_)},                                //
      {"column", std::to_string(column_)},                            //
      {"message", message_},                                          //
      {"flag", flag_}                                                 //
  };

  for (const auto kv : description)
    root.put(kv.first, kv.second);

  return root;
}

bool operator<(const diagnostic& lhs, const diagnostic& rhs)
{
  return std::tie(lhs.file_, lhs.line_, lhs.column_, lhs.message_, lhs.flag_) <
         std::tie(rhs.file_, rhs.line_, rhs.column_, rhs.message_, rhs.flag_);
}

bool operator==(const diagnostic& lhs, const diagnostic& rhs)
{
  return std::tie(lhs.file_, lhs.line_, lhs.column_, lhs.message_, lhs.flag_) ==
         std::tie(rhs.file_, rhs.line_, rhs.column_, rhs.message_, rhs.flag_);
}
}
