#include <iomanip>//setprecision
#include <iostream>//cout
#include "compare.h"

using namespace algorithm_custom;

int main()
{
    unsigned char c = 1;
    unsigned short s = 2;
    unsigned i = 3;
    unsigned long l = 4;
    int a = -1;
    float f = 2.0 / 3;
    double d = 2.0 / 3;

    float f1 = 20000000.0 / 3;
    double d1 = 20000000.0 / 3;
    
    std::cout << ( int)c << "<" << a << " " <<( less( c, a) ? "true" : "false")<< std::endl;
    std::cout << s << "<" << a << " " << ( less( s, a) ? "true" : "false")<< std::endl;
    std::cout << i << "<" << a << " " << ( less( i, a) ? "true" : "false")<< std::endl;
    std::cout << l << "<" << a << " " << ( less( l, a) ? "true" : "false")<< std::endl;
    std::cout << a << "<" << ( int)c << " " << ( less( a, c) ? "true" : "false")<< std::endl;
    std::cout << a << "<" << s << " " << ( less( a, s) ? "true" : "false")<< std::endl;
    std::cout << a << "<" << i << " " << ( less( a, i) ? "true" : "false")<< std::endl;
    std::cout << a << "<" << l << " " << ( less( a, l) ? "true" : "false")<< std::endl;
    std::cout << std::setprecision( 20);
    std::cout << f << "<" << d << " " << ( less( f, d) ? "true" : "false")<< std::endl;
    std::cout << d << "<" << f << " " << ( less( d, f) ? "true" : "false")<< std::endl;

    std::cout << d << "<=" << f << " " << ( less_equal( d, f) ? "true" : "false")<< std::endl;
    std::cout << d << ">=" << f << " " << ( greater_equal( d, f) ? "true" : "false")<< std::endl;
    std::cout << d << ">" << f << " " << ( greater( d, f) ? "true" : "false")<< std::endl;
    std::cout << d << "==" << f << " " << ( equal( d, f) ? "true" : "false")<< std::endl;
    
    std::cout << f1 << "<" << d1 << " " << ( less( f1, d1) ? "true" : "false")<< std::endl;
    return 0;
}
