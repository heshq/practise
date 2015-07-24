#include "stdafx.h"

#include <cstdio>
#include <cstring>
#include "big_integer.h"

int find_sqart_root( int target)
{
    if( target <= 0)
        return 0;
    int num = 1;
    if( num * num > target)
        num = num - ( num*num - target)/( 2*num) - 1;
    else if( ( num + 1)*( num + 1) <= target)
        num = num + ( target - ( num + 1)*( num + 1))/( 2*( num + 1)) + 1;
    return num;
}

int prime_test( int target)
{
    if( target <= 1)
        return 1;
    if( target == 2)
        return 0;
    int limit = find_sqart_root( target);
    int test_num = 2;
    while( test_num <= limit) {
        if( target % test_num == 0)
            return 1;
        test_num++;
    }
    return 0;
}

#define ASSERT( a, b, msg) if( a != b) puts( msg)
void generate_test_number()
{
    unsigned arr[ 30];
    memset( arr, 0, 30 * sizeof( int));
    int idx = 0;
    for( int i = 2; i < 100; i ++) {
        if( !prime_test( i))
            arr[ idx++] = i;
    }
    int i = 0;
    while( arr[ i] && arr[ i + 1]) {
        BigInteger *a = big_integer_create( arr + i, POSITIVE_NUMBER, 1);
        BigInteger *b = big_integer_create( arr + i + 1, POSITIVE_NUMBER, 1);
        BigInteger *result = big_integer_create( EMPTY_NUMBER, POSITIVE_NUMBER, 1);
        
        unsigned result_num = arr[ i] + arr[ i + 1];
        big_integer_assign( result, big_integer_add( a, b));
        printf( "add %u\n", result->data[ 0]);
        ASSERT( result->data[ 0], result_num, "add failed");

        result_num = arr[ i + 1] - arr[ i];
        big_integer_assign( result, big_integer_minus( b, a));
        printf( "minus %u\n", result->data[ 0]);
        ASSERT( result->data[ 0], result_num, "minus failed");

        result_num = arr[ i ] * arr[ i + 1];
        big_integer_assign( result, big_integer_multiply( a, b));
        printf( "multiply %u\n", result->data[ 0]);
        ASSERT( result->data[ 0], result_num, "mutiply failed");

        result_num = arr[ i + 1] / arr[ i];
        big_integer_assign( result, big_integer_divide( b, a));
        ASSERT( result->data[ 0], result_num, "divide failed");
        
        big_integer_destroy( result);
        big_integer_destroy( a);
        big_integer_destroy( b);
        i++;
    }
    puts("test1 passed");
}
#undef ASSERT

void test_3( unsigned base_number, unsigned power) {
    puts("test3--------------");
    BigInteger *a = big_integer_create( &base_number, POSITIVE_NUMBER, 1);
    unsigned test[ 10] = { 1,0,0,0,0,0,0,0,0,0};
    //unsigned one = 1;
    BigInteger *result = big_integer_create( test, POSITIVE_NUMBER, 10);
    for( unsigned i = 0; i < power; i++) 
        big_integer_assign( result, big_integer_multiply( result, a));
    printf( "0 %u 1 %u\n", result->data[ 0], result->data[ 1]);
	big_integer_output( result);
    for( unsigned i = 0; i < power; i++) 
        big_integer_assign( result, big_integer_divide( result, a));
	printf( "0 %u 1 %u\n", result->data[ 0], result->data[ 1]);
    big_integer_output( result);

    if( result->data[ 0] != 0) {
        puts("error");
    }
    big_integer_destroy( a);
    big_integer_destroy( result);
}

int _tmain(int argc, _TCHAR* argv[])
{
    generate_test_number(); 
    test_3( 100, 5);
    return 0;
}


