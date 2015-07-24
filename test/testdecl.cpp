#include <iostream>


using namespace std;

int add( int a, int b)
{  
    std::cout << "function add is call" << std::endl;
    return a + b;
}

int main()
{
    decltype( add( 1, 2) ) a = 1;
    //decltype( div( 1, 2) ) a = 1; //error
    std::cout << a << std::endl;
    return 0;
}
