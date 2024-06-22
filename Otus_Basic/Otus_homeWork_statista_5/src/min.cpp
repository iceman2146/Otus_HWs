#include "min.h"
Min::Min() : m_min{std::numeric_limits<double>::min()}
{
	name_child = "Min";
}
void Min::update(double next)
{
	if (next < m_min)
	{
		m_min = next;
	}
}

double Min::eval() const
{
	return m_min;
}
