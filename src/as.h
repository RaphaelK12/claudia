#ifndef AS_GUARD
#define AS_GUARD

#include <string>
#include <type_traits>

namespace detail {

/* floating point */
template <typename T, typename V>
auto as(const V& v) -> typename std::enable_if<std::is_floating_point<T>::value, T>::type
{
  return std::stold(v);
}

/* signed */
template <typename T, typename V>
auto as(const V& v) -> typename std::enable_if<std::is_integral<T>::value&& std::is_signed<T>::value, T>::type
{
  return std::stoll(v);
}

/* unsigned */
template <typename T, typename V>
auto as(const V& v) -> typename std::enable_if<std::is_integral<T>::value&& std::is_unsigned<T>::value, T>::type
{
  return std::stoull(v);
}

/* implicit conversion */
template <typename T, typename V>
auto as(const V& v) -> typename std::enable_if<std::is_convertible<V, T>::value, T>::type
{
  return v;
}
}

#endif
