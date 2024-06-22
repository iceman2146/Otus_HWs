#pragma once
#include "interface.h"
#include <limits>

class IStatistics;

class Max : public IStatistics
{
public:
    Max();
    void update(double next) override;
    double eval() const override;

private:
    double m_max;
};