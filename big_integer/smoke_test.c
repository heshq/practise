#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void number_2_string( unsigned number, char *string, size_t size) {
    memset( string, 0, size);
    memset( string, '0', size - 1);
    if( number) {
        size_t index = size - 1;
        while( number >= 10 && index > 0 ) {
            string[ index - 1] = 48 + number % 10;
            number = number / 10;
            index --;
        }
        if( number > 0 && index > 0)
            string[ index - 1] = 48 + number;
    }
}


#define ASSERT( number1, number2, a, b, msg)            \
              if( a != b) {                             \
                  printf( msg, number1, number2, a, b); \
                  failed_test ++;                       \
              }                                         \
              total_test++;
#define BUFFER_SIZE 12
void generate_test_number()
{
    puts("--------------test 1 begin--------------");
    unsigned arr[ 30];
    memset( arr, 0, 30 * sizeof( int));
    int idx = 0;
    for( int i = 2; i < 100; i ++) {
        if( !prime_test( i))
            arr[ idx++] = i;
    }
    int i = 0;
    char buffer[ BUFFER_SIZE];
    int total_test  = 0;
    int failed_test = 0;
    while( arr[ i] && arr[ i + 1]) {
        number_2_string( arr[ i], buffer, BUFFER_SIZE);
        BigInteger *a = big_integer_init( buffer);
        number_2_string( arr[ i + 1], buffer, BUFFER_SIZE);
        BigInteger *b = big_integer_init( buffer);
        BigInteger *result = big_integer_create( 0 , false);
        
        unsigned result_num = arr[ i] + arr[ i + 1];
        big_integer_assign( result, big_integer_add( a, b));
        ASSERT( arr[ i], arr[ i + 1], result->data[ 0], result_num, "failed:%u + %u = %u, should be %u\n");
        
        result_num = arr[ i + 1] - arr[ i];
        big_integer_assign( result, big_integer_minus( b, a));
        ASSERT( arr[ i + 1], arr[ i], result->data[ 0], result_num, "failed:%u - %u = %u, should be %u\n");
        
        result_num = arr[ i ] * arr[ i + 1];
        big_integer_assign( result, big_integer_multiply( a, b));
        ASSERT( arr[ i], arr[ i + 1], result->data[ 0], result_num, "failed:%u * %u = %u, should be %u\n");
        
        result_num = arr[ i + 1] / arr[ i];
        big_integer_assign( result, big_integer_divide( b, a));
        ASSERT( arr[ i + 1], arr[ i], result->data[ 0], result_num, "failed:%u / %u = %u, should be %u\n");
        
        result_num = arr[ i + 1] % arr[ i];
        big_integer_assign( result, big_integer_mod( b, a));
        ASSERT( arr[ i + 1], arr[ i], result->data[ 0], result_num, "failed:%u %% %u = %u, should be %u\n");
        
        big_integer_destroy( result);
        big_integer_destroy( a);
        big_integer_destroy( b);
        i++;
    }
    if( failed_test == 0) {
        printf( "test 1 passed, total test %d\n", total_test);
    }else{
        printf( "test 1 passed, total test %d, failed %d\n", total_test, failed_test);
    }
    puts("--------------test 1 over--------------\n\n\n");
}
#undef ASSERT


void big_integer_qsort( BigInteger **Number){
}

void test_2( ){}

void test_3( unsigned base_number, unsigned power) {
    puts("--------------test 3 begin--------------");
    char buffer[ BUFFER_SIZE];
    number_2_string( base_number, buffer, BUFFER_SIZE);
    BigInteger *base= big_integer_init( buffer);
    number_2_string( 1, buffer, BUFFER_SIZE);
    BigInteger *result = big_integer_init( buffer);
    for( unsigned i = 0; i < power; i++)
        big_integer_assign( result, big_integer_multiply( result, base));
    //big_integer_output( result);
    for( unsigned i = 0; i < power; i++) {
        big_integer_assign( result, big_integer_divide( result, base));
        //big_integer_output( result);
    }

    
    if( result->data[ 0] != 1) {
        puts( "test 3 failed");
    }else {
        puts( "test 3 pass");
    }
    big_integer_destroy( base);
    big_integer_destroy( result);
    puts("--------------test 3 over---------------");
}

int main() {
    generate_test_number();
    test_3( 1001, 12);
    return 0;
}


