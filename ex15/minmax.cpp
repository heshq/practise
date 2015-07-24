#include <iostream>
#include <vector>
#include "minmax.h"

int main()
{
    std::vector< int> vec;
    int arr[ 10];
    for( int i = 0; i < 10; i++ ) {
        vec.push_back( 20 - i );
        arr[ i] = 20 - i;
    }
    std::vector< int>::iterator iter = algorithm_custom::min_element( vec.begin(), vec.end());
    //if( iter != vec.end())
    std::cout << "min element in vec:" << *iter << std::endl;
    iter = algorithm_custom::max_element( vec.begin(), vec.end());
    std::cout << "max element in vec:" << *iter << std::endl;
    int *num = algorithm_custom::min_element( arr , arr + 10 ); 
    std::cout << "min element in arr:" << *num << std::endl;
    num = algorithm_custom::max_element( arr , arr + 10 ); 
    std::cout << "max element in arr:" << *num << std::endl;
    return 0;
}
