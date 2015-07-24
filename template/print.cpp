#include <iostream>

template< typename T>
void print( T t)
{
    std::cout << " " << t;
}

template< typename T, typename... V>
void print( T t, V... v)
{
    std::cout << " " << t;
    print( v...);
}

int main()
{
    print( 1, 2.1, 3u, 'a');
    std::cout << std::endl;
    return 0;
}
