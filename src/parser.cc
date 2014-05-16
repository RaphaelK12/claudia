#include <istream>
#include <ostream>
#include <regex>
#include <algorithm>
#include <stdexcept>

#include "config.h"
#include "pretty.h"
#include "parser.h"

namespace detail {

parser::parser(std::istream& in) : raw_{std::istreambuf_iterator<char>{in}, {}}
{
  /* file.h:line:column: warning: msg [-Wflag,Category] */
  std::regex pattern{config::diagnostic_format, std::regex::optimize};

  /* non-matches are silently ignored */
  std::sregex_iterator it{std::begin(raw_), std::end(raw_), pattern};

  std::transform(it, {}, std::back_inserter(diagnostics_), [](const decltype(*it) & match)->diagnostic {
    return {match[1], std::stoull(match[2]), std::stoull(match[3]), match[4], match[5]};
  });

  /* no std::set -- this way it's more memory friendly */
  std::sort(std::begin(diagnostics_), std::end(diagnostics_));
  std::unique(std::begin(diagnostics_), std::end(diagnostics_));
}

auto operator<<(std::ostream& out, const parser& in) -> std::ostream &
{
  for (const auto& diag : in.diagnostics_)
    out << diag << '\n';
  return out;
}
}
