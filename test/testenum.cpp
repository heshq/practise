#include <iostream>

enum{
    MODE_A = 1u,
    MODE_B = 2u,
    MODE_C = 4u,
    MODE_D = 8u
};

int main()
{
    std::cout<< ( 6 == ( MODE_B | MODE_C ) )<<std::endl;
}
