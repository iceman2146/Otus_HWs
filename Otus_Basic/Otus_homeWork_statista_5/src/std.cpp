#include "std.h"
Std::Std() : sum{0}, numCounter{0} { name_child = "Std"; }
double Std::eval() const
{
    {
        if (input_arr.empty())
        {
            return 0;
        }
        double temp_sum = 0.0;
        double sum = 0.0;
        sum = std::accumulate(input_arr.begin(), input_arr.end(), 0.0);
        double mean = static_cast<double>(sum / input_arr.size());
        std::vector<double> new_arr;
        for (std::size_t i = 0; i < input_arr.size(); i++)
        {

            temp_sum += (input_arr[i] - mean) * (input_arr[i] - mean);
        }
        temp_sum = temp_sum / input_arr.size();

        return std::sqrt(temp_sum);
    }
}

void Std::update(double next)
{
    input_arr.push_back(next);
}
