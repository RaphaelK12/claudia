#include <cstddef>
#include <istream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <utility>
#include <map>

#include <boost/property_tree/json_parser.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <boost/range/algorithm/unique.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <boost/regex.hpp>

#include "parser.h"

namespace claudia {

/*
 * multiline support missing in most environments; parse line-by-line
 * see: http://cplusplus.github.io/LWG/lwg-active.html#2343
 */
parser::parser(std::istream& in, const std::string& format)
{
  std::vector<std::string> lines;

  for (std::string line; std::getline(in, line);)
    lines.emplace_back(std::move(line));

  const boost::regex pattern{format, boost::regex::optimize};
  boost::smatch match;

  auto it = std::make_move_iterator(std::begin(lines));
  auto end = std::make_move_iterator(std::end(lines));

  /* exception safe parsing */
  decltype(diagnostics_) local;

  /* non-matches are silently ignored */
  std::for_each(it, end, [&](std::string line) {
    if (boost::regex_search(std::move(line), match, pattern)) {
      /* 0th sub-match is entire matched expression */
      if (match.size() - 1 != 5)
        throw std::runtime_error{"bad format: five groups required: file, line, column, message, flag"};

      local.emplace_back(match[1], std::stoull(match[2]), std::stoull(match[3]), match[4], match[5]);
    }
  });

  /* no std::set -- this way it's more memory friendly */
  boost::erase(local, boost::unique<boost::return_found_end>(boost::sort(local)));

  diagnostics_ = std::move(local);
}

void parser::report(std::ostream& out, bool want_summary) const
{
  property::ptree root;

  if (want_summary)
    root.add_child("summary", summary());

  root.add_child("diagnostics", report());

  property::write_json(out, root);
}

property::ptree parser::report() const
{
  property::ptree root;

  for (const auto diagnostic : diagnostics_)
    root.push_back(std::make_pair("", diagnostic.report()));

  return root;
}

property::ptree parser::summary() const
{
  property::ptree root;

  root.add_child("by_file", group_by_file());
  root.add_child("by_flag", group_by_flag());

  return root;
}

property::ptree parser::group_by_file() const
{
  property::ptree root;

  auto file_comp = [](const diagnostic& lhs, const diagnostic rhs) { return lhs.file < rhs.file; };
  std::map<diagnostic, std::size_t, decltype(file_comp)> by_file(file_comp);

  for (const auto diagnostic : diagnostics_)
    by_file[diagnostic] += 1;

  for (const auto kv : by_file)
    root.push_back(property::ptree::value_type(kv.first.file, property::ptree(std::to_string(kv.second))));

  return root;
}

property::ptree parser::group_by_flag() const
{
  property::ptree root;

  auto flag_comp = [](const diagnostic& lhs, const diagnostic rhs) { return lhs.flag < rhs.flag; };
  std::map<diagnostic, std::size_t, decltype(flag_comp)> by_flag(flag_comp);

  for (const auto diagnostic : diagnostics_)
    by_flag[diagnostic] += 1;

  for (const auto kv : by_flag)
    root.push_back(property::ptree::value_type(kv.first.flag, property::ptree(std::to_string(kv.second))));

  return root;
}
}
