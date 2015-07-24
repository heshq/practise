#include <iostream>
#include <vector>


int main()
{
    std::vector< int> vec;
    for( int i = 0; i< 10; i++)
        vec.push_back( i);
    std::vector< int>::iterator iter = vec.begin();
    std::cout<< sizeof( std::vector< int>::iterator::value_type)<<std::endl;
    return 0;
}


