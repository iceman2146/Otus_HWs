#include "mean.h"
Mean::Mean() : sum{0}, numCounter{0} { name_child = "Mean"; }
void Mean::update(double next)
{

	sum += next;

	++numCounter;
}

double Mean::eval() const
{
	return sum / numCounter;
}
