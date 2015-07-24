#include <iostream>
#include <vector>

#include "maximum.h"

using namespace std;
int main()
{
    vector< int> vec;
    for( int i = 0; i < 10; i ++){
        vec.push_back( i);
    }
    cout<< maximum( vec.begin(), vec.end())<<endl;
    int array[ 10];
    for( int i = 19; i >= 10; i --){
        array[ 19  - i ] = i;
    }
    cout<< maximum( array , array + 10)<< endl; 
    return 0;
}

