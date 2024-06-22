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
	Std();

	void update(double next) override;
	double eval() const override;

private:
	double sum;
	int numCounter;
	double *input_array = new double[numCounter];
	std::vector<double> input_arr;
};