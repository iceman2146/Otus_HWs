#include "procentil95.h"
Pct95::Pct95() : input_arr{} { name_child = "Pct95"; }
void Pct95::update(double next)
{
    input_arr.push_back(next);
}

double Pct95::eval() const
{
    if (std::is_sorted(input_arr.begin(), input_arr.end()))
    {

        const auto var_count = static_cast<size_t>(0.95 * input_arr.size());
        return input_arr[var_count];
    }
    else
    {

        std::vector<double> temp_arr = input_arr;
        std::sort(temp_arr.begin(), temp_arr.end());
        const auto var_count = static_cast<size_t>(0.95 * temp_arr.size());
        return temp_arr[var_count];
    }
}
