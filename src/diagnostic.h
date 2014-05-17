#ifndef DIAGNOSTIC_GUARD
#define DIAGNOSTIC_GUARD

#include <cstddef>
#include <string>
#include <iosfwd>

namespace detail {

class diagnostic {
private:
  std::string file_;
  std::size_t line_;
  std::size_t column_;
  std::string message_;
  std::string flag_;

public:
  diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag);

  auto csv(const std::string& delim = ",") const -> std::string;
  auto json(std::size_t indent = 2) const -> std::string;

  auto friend operator<(const diagnostic& lhs, const diagnostic& rhs) -> bool;
  auto friend operator>(const diagnostic& lhs, const diagnostic& rhs) -> bool;
  auto friend operator==(const diagnostic& lhs, const diagnostic& rhs) -> bool;
  auto friend operator!=(const diagnostic& lhs, const diagnostic& rhs) -> bool;

  auto friend operator<<(std::ostream& out, const diagnostic& in) -> std::ostream&;
};
}

#endif
