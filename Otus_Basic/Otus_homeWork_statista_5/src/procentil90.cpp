#include "procentil90.h"
Pct90::Pct90() : input_arr{} { name_child = "Pct90"; }
void Pct90::update(double next)
{
    input_arr.push_back(next);
}
void Pct90::Sort()
{
    std::sort(input_arr.begin(), input_arr.end());
}

double Pct90::eval() const
{

    if (std::is_sorted(input_arr.begin(), input_arr.end()))
    {

        const auto var_count = static_cast<size_t>(0.9 * input_arr.size());
        return input_arr[var_count];
    }
    else
    {

        std::vector<double> temp_arr = input_arr;
        std::sort(temp_arr.begin(), temp_arr.end());
        const auto var_count = static_cast<size_t>(0.9 * temp_arr.size());
        return temp_arr[var_count];
    }
}
