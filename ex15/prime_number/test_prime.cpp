#include <iostream>
#include "prime_number.h"

unsigned find_square_root( unsigned target)
{
    unsigned lower = 0;
    unsigned upper = target;
    while( lower < upper){
        if( ( ( lower + upper)/2 * ( lower + upper)/2 ) <= target &&
            ( ( lower + upper)/2 + 1)*( ( lower + upper)/2 + 1 ) > target )
            break;
        if( ( ( lower + upper)/2 + 1)*( ( lower + upper)/2 + 1 ) < target)
            lower = ( lower + upper )/2 + 1;
        else
            upper = ( lower + upper)/2 + 1;
    }
    return ( lower + upper)/2;
}

int main()
{
    //g++ test_prime.cpp -std=c++11 -Wall -ftemplate-depth=1001
    using namespace std;
    using namespace prime_util;
    //unsigned rst = FindSquareRoot< 4>::value;
    //unsigned rst = Square< 200>::value;
    //cout << rst << endl;
    PrimeNumbers< 1000> primer;
    bool *prime_number = reinterpret_cast< bool *> ( &primer);
    for ( int i = 0; i < 1000 ; i ++ )
        if( prime_number[ i])
            cout << i << " ";
    cout << endl;
    //cout << prime_util_inner::Square< 100>::value << endl;
    return 0;
}
