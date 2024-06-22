#include "max.h"

Max::Max() : m_max{std::numeric_limits<double>::lowest()}
{
    name_child = "Max";
}

void Max::update(double next)
{
    if (next > m_max)
    {
        m_max = next;
    }
}

double Max::eval() const
{
    return m_max;
}
