#include <istream>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <utility>

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
    if (boost::regex_search(std::move(line), match, pattern))
      local.emplace_back(match[1], std::stoull(match[2]), std::stoull(match[3]), match[4], match[5]);
  });

  /* no std::set -- this way it's more memory friendly */
  boost::erase(local, boost::unique<boost::return_found_end>(boost::sort(local)));

  diagnostics_ = std::move(local);
}

void parser::report(std::ostream& out, bool summary) const
{
  boost::property_tree::ptree root;

  if (summary)
    root.add_child("summary", do_summary());

  root.add_child("diagnostics", do_report());

  boost::property_tree::write_json(out, root);
}

boost::property_tree::ptree parser::do_summary() const
{
  boost::property_tree::ptree root;

  // XXX: statistics
  // root.put(k, v);

  return root;
}

boost::property_tree::ptree parser::do_report() const
{
  boost::property_tree::ptree root;

  for (const auto diagnostic : diagnostics_)
    root.push_back(std::make_pair("", diagnostic.report()));

  return root;
}
}
