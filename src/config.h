#ifndef CONFIG_GUARD
#define CONFIG_GUARD

#include <string>

namespace detail {
namespace config {
  namespace {
    /* see parser.cc: 5 groups: file, line, column, warning, flag */
    const char* const diagnostic_format{"(.+):(\\d+):(\\d+): warning: (.+) \\[(.+)\\]"};
  }
}
}

#endif
