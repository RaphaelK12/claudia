#ifndef PRETTY_GUARD
#define PRETTY_GUARD

#include <cstddef>
#include <tuple>

namespace detail {

template <typename Out, typename T, std::size_t N>
struct pretty_tuple {
  static auto print(Out& out, const T& t) -> void
  {
    pretty_tuple<Out, T, N - 1>::print(out, t);
    out << ", " << std::get<N - 1>(t);
  }
};

template <typename Out, typename T>
struct pretty_tuple<Out, T, 1> {
  static auto print(Out& out, const T& t) -> void
  {
    out << std::get<0>(t);
  }
};

template <typename Out, typename... Args>
auto operator<<(Out& out, const std::tuple<Args...>& t) -> Out &
{
  pretty_tuple<Out, decltype(t), sizeof...(Args)>::print(out, t);
  return out;
}
}

#endif
