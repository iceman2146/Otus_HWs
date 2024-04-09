#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

/**
 * @file ip_print.h
 *
 * Шаблонные методы для песати адреса, представлено разными типами
 */

/**
 * @brief Шаблон для печати целых.
 */
/// @brief
/// @tparam T
/// @tparam type
/// @param data
template <typename T, typename std::enable_if<std::is_integral<T>::value,
                                              bool>::type = true>
void print_ip(T data) {
  static constexpr size_t size_byte = sizeof(T);
  for (auto i = size_byte; i--;) {
    std::cout << ((data >> (i << 3)) & 0xff);
    if (i > 0)
      std::cout << '.';
  }
  std::cout << std::endl;
}
/**
 * @brief Шаблон для печати строки.
 */
void print_ip(const std::string &str) { std::cout << str << std::endl; }
/**
 * @brief Шаблон для печати вектора или строки.
 */
template <typename T,
          typename std::enable_if<std::is_same<T, std::vector<int>>::value or
                                      std::is_same<T, std::list<short>>::value,
                                  bool>::type = true>
void print_ip(T container) {
  for (auto it = container.begin(); it != container.end(); ++it) {
    std::cout << *it;
    if (it != prev(container.end()))
      std::cout << '.';
  }
  std::cout << std::endl;
}

/**
 * @brief Шаблон для печати кортежа.
 */
template <typename TypeFirst, typename... Types>
void print_tuple(const TypeFirst &tFirst, const Types &...tArgs) {

  std::cout << tFirst << '.';
  auto index = sizeof...(Types) - 1;

  auto printElem = [&tFirst, &index](const auto &x) {
    std::cout << x;

    if (index-- > 0)
      std::cout << '.';
  };

  (printElem(tArgs), ...);
  std::cout << std::endl;
}

template <typename... Types>
static void print_ip(const std::tuple<Types...> &tuple) {
  std::apply(print_tuple<Types...>, tuple);
}