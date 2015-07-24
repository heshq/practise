#include <stdio.h>
#include <stdbool.h>

int main()
{
    int a = 2;
    if( a == true)
        printf( " a == true\n");
    else
        printf( " a != true\n");
    bool b = true;
    unsigned long l = true;
    printf( "the size of bool type  is %lu, the size of true is %lu\n", sizeof( b), sizeof( true));
    printf( "the value of true is %lu\n", l); 
    return 0;
}
