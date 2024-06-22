#pragma once
#include <cmath>
#include <vector>
#include <numeric>
#include "interface.h"
// арифметическое среднее
class IStatistics;
class Mean : public IStatistics
{
public:
	Mean();

	void update(double next) override;
	double eval() const override;

private:
	double sum;
	int numCounter;
};
