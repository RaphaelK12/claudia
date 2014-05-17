#include <ostream>
#include <utility>
#include <tuple>
#include <algorithm>

#include "diagnostic.h"

namespace detail {

diagnostic::diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag)
    : file_{std::move(file)}, line_{line}, column_{column}, message_{std::move(message)}, flag_{std::move(flag)}
{
}

namespace {
  /* poor man's escaping */
  auto escaped(std::string word) -> std::string
  {
    std::replace(std::begin(word), std::end(word), '"', '\'');
    return "\"" + word + "\"";
  }
}

auto diagnostic::csv(const std::string& delim) const -> std::string
{
  std::string out;

  out += escaped(file_) + delim;
  out += std::to_string(line_) + delim;
  out += std::to_string(column_) + delim;
  out += escaped(message_) + delim;
  out += escaped(flag_);

  return out;
}

auto diagnostic::json(std::size_t indent) const -> std::string
{
  std::string out;
  out += std::string(indent, ' ') + "{\n";

  out += std::string(2 * indent, ' ') + "\"filename\": " + escaped(file_) + ",\n";
  out += std::string(2 * indent, ' ') + "\"line\": " + std::to_string(line_) + ",\n";
  out += std::string(2 * indent, ' ') + "\"column\": " + std::to_string(column_) + ",\n";
  out += std::string(2 * indent, ' ') + "\"message\": " + escaped(message_) + ",\n";
  out += std::string(2 * indent, ' ') + "\"flag\": " + escaped(flag_) + "\n";

  return out += std::string(indent, ' ') + "}";
}

auto operator<(const diagnostic& lhs, const diagnostic& rhs) -> bool
{
  return std::tie(lhs.file_, lhs.line_, lhs.column_, lhs.message_, lhs.flag_) <
         std::tie(rhs.file_, rhs.line_, rhs.column_, rhs.message_, rhs.flag_);
}

auto operator>(const diagnostic& lhs, const diagnostic& rhs) -> bool
{
  return std::tie(lhs.file_, lhs.line_, lhs.column_, lhs.message_, lhs.flag_) >
         std::tie(rhs.file_, rhs.line_, rhs.column_, rhs.message_, rhs.flag_);
}

auto operator==(const diagnostic& lhs, const diagnostic& rhs) -> bool
{
  return std::tie(lhs.file_, lhs.line_, lhs.column_, lhs.message_, lhs.flag_) ==
         std::tie(rhs.file_, rhs.line_, rhs.column_, rhs.message_, rhs.flag_);
}

auto operator!=(const diagnostic& lhs, const diagnostic& rhs) -> bool
{
  return !(lhs == rhs);
}

auto operator<<(std::ostream& out, const diagnostic& in) -> std::ostream &
{
  return out << in.file_ << ", " << in.line_ << ", " << in.column_ << ", " << in.message_ << ", " << in.flag_;
}
}
