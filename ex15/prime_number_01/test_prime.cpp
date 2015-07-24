#include <iostream>
#include "prime_number_03.h"

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
    using namespace std;
    using namespace prime_util;
    //unsigned rst = FindSquareRoot< 4>::value;
    //unsigned rst = Square< 200>::value;
    //cout << rst << endl;
    PrimeNumber< 1000> primer;
    bool *prime_number = reinterpret_cast< bool *> ( &primer);
    for ( int i = 0; i < 1000 ; i ++ )
        if( prime_number[ i])
            cout << i << " ";
    cout << endl;
    //cout << prime_util_inner::Square< 100>::value << endl;
    return 0;
}
