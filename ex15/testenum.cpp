#include "binary.h"
#include <iostream>

enum{
    MODE_A = Binary< 1>::value,
    MODE_B = Binary< 10>::value,
    MODE_C = Binary< 100>::value,
    MODE_D = Binary< 1000>::value
};

int main()
{
    std::cout<< Binary< 0110>::value <<std::endl;
    std::cout<< (  MODE_B | MODE_C ) <<std::endl;
    //std::cout<< ( Binary< 0110>::value == ( MODE_B | MODE_C ) )<<std::endl;
}
