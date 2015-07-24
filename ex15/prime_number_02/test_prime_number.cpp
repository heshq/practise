#include <iostream>
#include "prime_number.h"

using namespace std;
using namespace prime_number_util;
int main()
{
    //bool arr[ 1000] = { false};
    //for( int i = 0; i < 1000; i ++) {
    //    arr[ i] = true;
    //}
    //for( int i = 2; i < 1000 ; i++) {
    //    if( arr[ i ]){
    //        for( int j = i + i ; j < 1000; j += i)
    //            arr[ j] = false;
    //    }
    //}

    //for( int i = 0; i < 1000; i ++) {
    //    if( arr[ i])
    //        cout << i << " " ;
    //}
    //cout << endl;

    //Number< 200> number;
    //bool * primer = reinterpret_cast< bool *>( &number);
    //for( int i = 0 ; i < 200; i ++) {
    //    if( primer[ i])
    //        cout << i << " ";
    //}
    //cout << endl;

    //clang++ -std=c++11 -ftemplate-depth=1001  testprimer.cpp
    Number< 1000u> number1;
    bool * prime = reinterpret_cast< bool *>( &number1);
    for( int i = 0 ; i < 1000; i ++) {
        if( prime[ i])
            cout << i << " ";
    }
    cout << endl;

    //cout << ( Number< 1u>::is_primer ? "1 is a primer" : "1 is not a primer" ) << endl;
    return 0;
}
