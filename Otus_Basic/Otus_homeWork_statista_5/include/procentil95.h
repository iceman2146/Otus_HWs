#pragma once
#include <vector>
#include <algorithm>

#include "interface.h"

class Pct95 : public IStatistics
{
public:
    Pct95();
    void update(double next) override;

    double eval() const override;

private:
    std::vector<double> input_arr;
};