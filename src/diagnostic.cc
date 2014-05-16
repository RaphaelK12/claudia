#include <ostream>
#include <utility>
#include <tuple>

#include "diagnostic.h"

namespace detail {

diagnostic::diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag)
    : file_{std::move(file)}, line_{line}, column_{column}, message_{std::move(message)}, flag_{std::move(flag)}
{
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
