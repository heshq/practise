#include <stdio.h>

int main()
{
    int x; // convert this from using 5 bits to a full int
    int r; // resulting sign extended number goes here
    scanf( "%d", &x);
    struct {signed int x:5;} s;
    r = s.x = x;
    printf( "the value if r is %d\n", r);
    return 0;
}
