#include "ip_lib.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
template <typename T, typename... Args>
auto ip_address(T number, Args... args) {
  ipv4 result = ip_address(args...);
  result.push_back(number);
  std::reverse(result.begin(), result.end());
  return result;
}
int main() {

  try {
    std::vector<ipv4> ip_pool;

    for (std::string line; std::getline(std::cin, line);) {
      auto v = split(line, '\t');
      ip_pool.push_back(to_int(split(v.at(0), '.')));
    }

    std::sort(ip_pool.begin(), ip_pool.end(),
                [](auto a, auto b) { return (a > b); });
    std::cout << ip_pool;

    ip_filter(ip_pool, ip_address(1));
    

    ip_filter(ip_pool, ip_address(46, 70));
    

    ip_filter_any(ip_pool, 46);
    

  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}