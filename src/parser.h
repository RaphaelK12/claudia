#ifndef PARSER_GUARD
#define PARSER_GUARD

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

  auto friend operator<<(std::ostream& out, const parser& in) -> std::ostream&;
};
}

#endif
