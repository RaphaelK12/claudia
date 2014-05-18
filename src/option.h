#ifndef OPTION_GUARD
#define OPTION_GUARD

#include <cstdlib>
#include <string>
#include <vector>
#include <iosfwd>

#include "as.h"

namespace detail {

class option {
private:
  std::vector<std::string> arguments_;
  std::string filename_;
  std::string parameter_;

public:
  option(int argc, char** argv, std::string parameter);
  option(int argc, char** argv);

  auto usage(std::ostream& out, const std::string& msg) const -> std::ostream&;
  auto abort(const std::string& msg) const -> decltype(EXIT_FAILURE);

  auto require(decltype(arguments_)::size_type n) const -> bool;

  template <typename T>
  auto get(decltype(arguments_)::size_type n) -> decltype(as<T>(arguments_.at(n)))
  {
    return as<T>(arguments_.at(n));
  }

  auto friend operator<<(std::ostream& out, const option& in) -> std::ostream&;
};
}

#endif
