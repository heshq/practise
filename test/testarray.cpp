#include <iostream>

template< unsigned N>
struct array{
    struct array< N - 1> prifix;
    unsigned value = N;
};

template<>
struct array< 0>{
    unsigned value = 0;
};

int main()
{
    array< 100> a;
    //std::cout << a.value << std::endl;
    //std::cout << a.prifix.prifix.prifix.value << std::endl;
    //std::cout << &(a.value) << " " << &(a.prifix.prifix.prifix.value) << std::endl;
    unsigned *arr = reinterpret_cast< unsigned *>( &a);
    std::cout <<  *( arr + 20) << std::endl;
    return 0;
}
