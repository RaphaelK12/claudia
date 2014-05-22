#ifndef DIAGNOSTIC_GUARD
#define DIAGNOSTIC_GUARD

#include <cstddef>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace claudia {

class diagnostic {
public:
  diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag);

  boost::property_tree::ptree report() const;

  bool friend operator<(const diagnostic& lhs, const diagnostic& rhs);
  bool friend operator==(const diagnostic& lhs, const diagnostic& rhs);

private:
  std::string file_;
  std::size_t line_;
  std::size_t column_;
  std::string message_;
  std::string flag_;
};
}

#endif
