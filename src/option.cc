#include <iostream>
#include <ostream>
#include <stdexcept>
#include <iterator>
#include <tuple>

#include "option.h"

namespace detail {

option::option(int argc, char** argv, std::string parameter)
    : arguments_{argv, argv + argc}, filename_{}, parameter_{std::move(parameter)}
{
  if (arguments_.size() < 1)
    throw std::runtime_error{"illegal arguments: filenamename always present"};

  std::tie(filename_, arguments_) = split();
}

option::option(int argc, char** argv) : option(argc, argv, "")
{
}

auto option::split() const -> std::pair<decltype(filename_), decltype(arguments_)>
{
  return {arguments_[0], {std::begin(arguments_) + 1, std::end(arguments_)}};
}

auto option::usage(std::ostream& out, const std::string& msg) const -> std::ostream &
{
  return out << "usage: " << filename_ << ' ' << parameter_ << '\n' << "aborted: " << msg;
}

auto option::abort(const std::string& msg) const -> decltype(EXIT_FAILURE)
{
  usage(std::cerr, msg) << std::endl;
  return EXIT_FAILURE;
}

auto option::require(decltype(arguments_)::size_type n) const -> bool
{
  return arguments_.size() >= n;
}

auto operator<<(std::ostream& out, const option& in) -> std::ostream &
{
  return out << in.parameter_;
}
}
