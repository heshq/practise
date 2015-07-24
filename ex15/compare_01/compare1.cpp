#include <iostream>
#include "compare.h"

int main()
{
    float a = 2.0 / 3;
    long double b = 2.0 / 3;
    std::cout<< ( compare( a, b) ? "true": "false")<<std::endl;
    std::cout<< ( compare( b, a) ? "true": "false")<<std::endl;

    float c = 2.0 / 3;
    long double d = 2.0 / 3;
    std::cout<< ( compare( c, d) ? "true": "false")<<std::endl;
    std::cout<< ( compare( d, c) ? "true": "false")<<std::endl;

    std::cout<< ( compare( -1, 1u) ? "true": "false")<<std::endl;

    std::cout<< ( compare( -1, 5) ? "true": "false")<<std::endl;
    char c1 = 255;
    std::cout<< ( compare( c1 , 0) ? "true": "false")<<std::endl;
}


//bool compare( float a, double b)
//{
//    return a < b - FLT_EPSILON / 2;
//}

//bool compare( double a, float b)
//{
//    return a + FLT_EPSILON / 2 < b;
//}


//bool compare( float a, long double b)
//{
//    return a < b - FLT_EPSILON / 2;
//}

//bool compare( long double a, float b)
//{
//    return a + FLT_EPSILON / 2 < b;
//}

//bool compare( double a, long double b)
//{
//    return a < b - DBL_EPSILON / 2;
//}

//bool compare( long double a, double b)
//{
//    return a + DBL_EPSILON / 2 < b;
//}