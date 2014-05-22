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

  void report(std::ostream& out, bool summary = true) const;

private:
  std::vector<diagnostic> diagnostics_;
  
  boost::property_tree::ptree do_summary() const;
  boost::property_tree::ptree do_report() const;
};
}

#endif
