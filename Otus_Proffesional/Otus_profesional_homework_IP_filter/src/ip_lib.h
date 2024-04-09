#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


using ipv4 = std::vector<int>;
using ip_pool = std::vector<ipv4>;

std::vector<std::string> split(const std::string &, char);

std::ostream &operator<<(std::ostream &, const ipv4 &);
std::ostream &operator<<(std::ostream &, const ip_pool &);

ipv4 ip_address();
ipv4 to_int(std::vector<std::string> &&);

void ip_filter(const ip_pool &, const ipv4 &);
void ip_filter_any(const ip_pool &, int);
