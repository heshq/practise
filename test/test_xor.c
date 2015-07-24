#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a = 1;
    int b = 2;
    printf( "%d, %d\n", a ^ b ^ b, a ^ ( b ^ b));

    unsigned v = 0xff00;
    unsigned m = 0xff;
    bool b = false;
    //if( b)
    //    v |= m;
    //else
    //    v &= ( ~m);
    v = ( v | m)
    printf( "%x\n", v);
    return 0;
}
