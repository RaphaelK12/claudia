#include <istream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <regex>

#include "config.h"
#include "pretty.h"
#include "parser.h"

namespace detail {

/*
 * multiline support missing in most environments; parse line-by-line
 * see: http://cplusplus.github.io/LWG/lwg-active.html#2343
 */
parser::parser(std::istream& in)
{
  std::vector<std::string> raw;

  for (std::string line; std::getline(in, line);) {
    raw.emplace_back(std::move(line));
  }

  std::regex pattern{config::diagnostic_format, std::regex::optimize};
  std::smatch match;

  auto it = std::make_move_iterator(std::begin(raw));
  auto end = std::make_move_iterator(std::end(raw));

  /* transform not possible: in case of non-matches we're not able to always return a diagnostic object */
  std::for_each(it, end, [&](std::string line) {
    /* non-matches are silently ignored */
    if (std::regex_search(std::move(line), match, pattern)) {
      diagnostics_.emplace_back(match[1], std::stoull(match[2]), std::stoull(match[3]), match[4], match[5]);
    }
  });

  /* no std::set -- this way it's more memory friendly */
  std::sort(std::begin(diagnostics_), std::end(diagnostics_));
  auto trunc = std::unique(std::begin(diagnostics_), std::end(diagnostics_));
  diagnostics_.erase(trunc, std::end(diagnostics_));
}

auto operator<<(std::ostream& out, const parser& in) -> std::ostream &
{
  for (const auto& diag : in.diagnostics_)
    out << diag << '\n';
  return out;
}
}
