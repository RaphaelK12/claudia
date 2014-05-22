#ifndef DIAGNOSTIC_GUARD
#define DIAGNOSTIC_GUARD

#include <cstddef>
#include <string>

#include <boost/property_tree/ptree.hpp>

namespace claudia {

namespace property = boost::property_tree;

struct diagnostic {
  diagnostic(std::string file, std::size_t line, std::size_t column, std::string message, std::string flag);

  property::ptree report() const;

  std::string file;
  std::size_t line;
  std::size_t column;
  std::string message;
  std::string flag;
};

bool operator<(const diagnostic& lhs, const diagnostic& rhs);
bool operator==(const diagnostic& lhs, const diagnostic& rhs);
}

#endif
