#include <limits.h>
#include <stdio.h>

int main()
{
    int a;
    scanf( "%d", &a);
    //a = a >= 0 ? a : ~a + 1;
    int mask = a >> CHAR_BIT * sizeof( int) - 1;
    //a = ( a + mask) ^ mask;
    a = ( a ^ mask) - mask;
    printf( "%d\n", a);
    return 0;
}
