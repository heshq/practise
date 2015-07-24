#include <limits.h>//CHAR_BIT
#include <stdio.h>
#include <stdlib.h> //malloc
#include <string.h>//memset

#define SPLICE ( CHAR_BIT / 2)
#define MASK ( ( 1 << ( SPLICE + 1)) - 1 )
int big_integer_multiply_inner( unsigned *left, size_t left_size, unsigned *right, size_t right_size, unsigned *result)
{
    int carry_bit = 0;
    for( size_t i = 0; i < left_size; i ++) {
        for( size_t j = 0; j < right_size; j ++) {
            //use karatsuba algorithm
            unsigned x0 = left[ i] &  MASK;
            unsigned x1 = left[ i] >> SPLICE;
            unsigned y0 = right[ j] &  MASK;
            unsigned y1 = right[ j] >> SPLICE;
            unsigned z0 = x0 * y0;
            unsigned z1 = x1 * y1;
            unsigned z2 = ( x1 + x0) * ( y1 + y0) - z0 - z1;
            if( ( z0 >> 1 + result[ i + j] >> 1 + z0 & result[ i + j] & 0x1) >> ( CHAR_BIT - 1))
                carry_bit++;
            result[ i + j] += z0;
            if( ( z1 >> 1 + result[ i + j] >> 1 + z1 & result[ i + j] & 0x1) >> ( CHAR_BIT - 1))
                carry_bit++;
            result[ i + j] += z1;
            if( ( z2 >> 1 + result[ i + j] >> 1 + z2 & result[ i + j] & 0x1) >> ( CHAR_BIT - 1))
                carry_bit++;
            result[ i + j] += z2;

            size_t k = i + j + 1;
            while( carry_bit) {
                int next_carry_bit = ( ( result[ k] >> 1)+ ( carry_bit >> 1) + ( result[ k] & carry_bit & 0x1) ) 
                    >> ( CHAR_BIT - 1);
                result[ k] += carry_bit;
                carry_bit = next_carry_bit;
                k++;
            }
        }
    }
}

#undef SPLICE
#undef MASK

int main()
{
    unsigned *left = malloc( sizeof( unsigned) * 5);
    unsigned *right = malloc( sizeof( unsigned) * 5);
    unsigned *result= malloc( sizeof( unsigned) * 9);
    memset( left, 0, 5);
    for( size_t idx = 0; idx < 5; idx++)
        left[ idx] = idx + 1;
    memset( right, 0, 5);
    right[ 1] = 2;
    big_integer_multiply_inner( left, 5, right, 5, result);
    for( size_t idx = 0; idx < 9; idx ++)
        printf( "%u ", result[ 8 - idx]);
    puts("");
    return 0;
}
