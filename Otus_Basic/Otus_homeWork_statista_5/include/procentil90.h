#pragma once
#include <vector>
#include <algorithm>

#include "interface.h"

class Pct90 : public IStatistics
{
public:
    Pct90();

    void update(double next) override;
    void Sort();
    double eval() const override;

private:
    std::vector<double> input_arr;
};
