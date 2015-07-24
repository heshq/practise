#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    int v, sign;
    scanf( "%d", &v);
    //sign = -( v < 0);
    //sign =  v >> CHAR_BIT*sizeof( int) - 1;
    //sign = - ( int)( ( unsigned int)v >> CHAR_BIT*sizeof( int) - 1);
    //sign = ( v > 0) - ( v < 0);
    //sign = v != 0 | v >> CHAR_BIT*sizeof( int) - 1;
    sign = 1 ^ ( ( unsigned)v >> CHAR_BIT*sizeof( int) - 1);
    printf("the value of sign is %d\n", sign);
    return 0;
}
