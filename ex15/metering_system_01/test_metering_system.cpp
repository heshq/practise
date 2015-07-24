#include <iostream>
#include "metering_system.h"

using namespace std;
using namespace metering_system;
int main()
{
    Metering< BS,unsigned> test( 2);
    Metering< BS,int> bs1( 2);
    Metering< BS,int> bs2( 2);
    Metering< IS,int> is1( 4);
    Metering< IS,int> is2( 4);
    std::cout << ( bs1 + bs2)( MS::bs) << std::endl;
    std::cout << ( bs1 - bs2)( MS::bs) << std::endl;
    std::cout << ( bs1 + 1)( MS::bs) << std::endl;
    std::cout << ( bs1 - 1)( MS::bs) << std::endl;
    std::cout << ( is1 + is2)( MS::is) << std::endl;
    std::cout << ( is1 - is2)( MS::is) << std::endl;
    std::cout << ( is1 + 1)( MS::is) << std::endl;
    std::cout << ( is1 - 1)( MS::is) << std::endl;

    std::cout << is1( MS::is)*3 << std::endl;
    std::cout << is1( MS::is)/2 << std::endl;

    std::cout << ( bs1 < 1 ? "bs1 < 1" : "bs1 < 1 false") << std::endl;
    std::cout << ( bs1 <= 1 ? "bs1 <= 1" : "bs1 <= 1 false") << std::endl;
    std::cout << ( bs1 > 1 ? "bs1 > 1" : "bs1 > 1 false") << std::endl;
    std::cout << ( bs1 >= 1 ? "bs1 >= 1" : "bs1 >= 1 false") << std::endl;
    std::cout << ( bs1 == 1 ? "bs1 == 1" : "bs1 == 1 false") << std::endl;
    std::cout << ( bs1 != 1 ? "bs1 != 1" : "bs1 != 1 false") << std::endl;
    //bs1 < is1;
    //bs1 <= is1;
    //bs1 > is1;
    //bs1 >= is1;
    //bs1 == is1;
    //bs1 != is1;
    return 0;
}
