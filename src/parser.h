#ifndef PARSER_GUARD
#define PARSER_GUARD

#include <cstddef>
#include <string>
#include <vector>
#include <iosfwd>

#include "diagnostic.h"

namespace detail {

class parser {
private:
  std::vector<diagnostic> diagnostics_;

public:
  parser(std::istream& in);

  auto csv(const std::string& delim = ",", bool header = true) const -> std::string;
  auto json(std::size_t indent = 2) const -> std::string;

  auto friend operator<<(std::ostream& out, const parser& in) -> std::ostream&;
};
}

#endif
