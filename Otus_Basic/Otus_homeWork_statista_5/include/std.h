#pragma once
#include <cmath>
#include <vector>
#include <numeric>
#include "interface.h"
// среднеквадратическое отклонение
class IStatistics;

class Std : public IStatistics
{
public:
	Std() : sum{0}, numCounter{0}
	{
	}

	void update(double next) override
	{
		input_arr.push_back(next);
	}

	double eval() const override
	{
		double temp_sum = 0.0;
		double sum = 0.0;
		sum = std::accumulate(input_arr.begin(), input_arr.end(), 0.0);
		double mean = static_cast<double>(sum / input_arr.size());
		std::vector<double> new_arr;
		for (int i = 0; i < input_arr.size(); i++)
		{

			temp_sum += (input_arr[i] - mean) * (input_arr[i] - mean);
		}
		temp_sum = temp_sum / input_arr.size();

		return std::sqrt(temp_sum);
	}

	const char *name() const override
	{

		return "std";
	}

private:
	double sum;
	int numCounter;
	double *input_array = new double[numCounter];
	std::vector<double> input_arr;
};