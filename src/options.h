#ifndef OPTIONS_GUARD
#define OPTIONS_GUARD

#include <boost/program_options.hpp>

namespace claudia {

namespace options = boost::program_options;

options::options_description make_options_description();
options::positional_options_description make_positional_options_description();
}

#endif
