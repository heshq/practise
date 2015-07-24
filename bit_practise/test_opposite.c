#include <stdio.h>


int main()
{
    int a,b,sign;
    a = 0xffffff00;
    b = 0x000000ff;
    sign =  ( a ^ b) < 0;
    if( sign)
        printf("it is opposite\n");
    else
        printf("it is not opposite\n");
    return 0;
}
