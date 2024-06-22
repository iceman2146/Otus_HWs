#pragma once
#include "interface.h"
#include <limits>

class IStatistics;

class Min : public IStatistics
{
public:
	Min();

	void update(double next);
	double eval() const override;

private:
	double m_min;
};
