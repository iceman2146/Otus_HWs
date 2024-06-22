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
	Mean() : sum{0}, numCounter{0}
	{
	}

	void update(double next) override
	{

		sum += next;

		++numCounter;
	}

	double eval() const override
	{
		return sum / numCounter;
	}

	const char *name() const override
	{
		return "mean";
	}

private:
	double sum;
	int numCounter;
};
