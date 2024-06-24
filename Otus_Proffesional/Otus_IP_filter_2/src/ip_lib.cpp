#include "ip_lib.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> output;

    size_t start = 0;
    size_t stop = str.find_first_of(d);

    while (stop != std::string::npos)
    {
        output.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    output.push_back(str.substr(start));

    return output;
}

ipv4 to_int(std::vector<std::string> &&IP)
{
    ipv4 result;
    for (const auto &item : IP)
        result.push_back(std::stoi(item));
    return result;
}

std::ostream &operator<<(std::ostream &stream, const ipv4 &ipv4)
{
    for (auto i = 0; i < ipv4.size(); ++i)
    {
        stream << ipv4.at(i);
        if (i != ipv4.size() - 1)
            stream << '.';
    }
    return stream;
}
std::ostream &operator<<(std::ostream &stream, const ip_pool &ip_pool)
{
    for (const auto &ipv4 : ip_pool)
        stream << ipv4 << '\n';
    return stream;
}

ipv4 ip_address()
{
    return ipv4(0);
}

void ip_filter(const ip_pool &ip_pool, const ipv4 &ipv4)
{
    std::for_each(ip_pool.begin(), ip_pool.end(), [=](auto a)
                  {
                    int i = 0;
                    for (auto item : ipv4)
                if (item != a.at(i))
                    return;
                else
                    ++i;
            std::cout << a << '\n'; });
}

void ip_filter_any(const ip_pool &ip_pool, int number)
{
    std::for_each(ip_pool.begin(), ip_pool.end(), [=](auto a)
                  {
            for (auto item : a)
                if (item == number)
                {
                    std::cout << a << '\n';
                    return;
                } });
}
