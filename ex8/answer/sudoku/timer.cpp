#include <ctime>
#include "timer.h"

void
Timer::begin()
{
	_begin = clock();
}

void
Timer::end()
{
	_end = clock();
}

float
Timer::seconds() const
{
	return float( _end - _begin) / CLOCKS_PER_SEC;
}

