#ifndef PARSER_GUARD
#define PARSER_GUARD

#include <string>
#include <vector>
#include <iosfwd>

#include "diagnostic.h"

namespace claudia {

class parser {
public:
  parser(std::istream& in, const std::string& format);

  void report(std::ostream& out, bool want_summary = true) const;

private:
  std::vector<diagnostic> diagnostics_;

  property::ptree report() const;

  /* XXX: generic group_by(cmp) */
  property::ptree summary() const;
  property::ptree group_by_file() const;
  property::ptree group_by_flag() const;
};
}

#endif
