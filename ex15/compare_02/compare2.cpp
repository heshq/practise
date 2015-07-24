#include "compare.h"

using namespace custom_compare;

template<>
bool
less< float, double>::operator()( float a, double b)
{
	return a < ( float)b;
}

template<>
bool
less< double, float>::operator()( double a, float b)
{
	return ( float ) a < b;
}

template<>
bool
less< float, long double>::operator()( float a, long double b){
	return a < ( float) b;
}

template<>
bool
less< long double, float>::operator()( long double a, float b){
	return ( float) a < b;
}

template<>
bool
less< double, long double>::operator()( double a, long double b)
{
	return a < ( double) b;
}

template<>
bool
less< long double, double>::operator()( long double a, double b)
{
	return ( double) a < b;
}