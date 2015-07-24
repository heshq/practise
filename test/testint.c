#include <limits.h>
#include <stdio.h>
#include <stdbool.h>

int main()
{
    //int lnth = sizeof( int);
    int a;
    scanf("%d",&a);
    //printf( "%d\n", a);
    //printf( "%d\n",   ( a >> ( CHAR_BIT * lnth - 1 )) & 1);  
    bool is_pow = false;
    for( int i = 0; i < sizeof( int) * CHAR_BIT; i++){
        if( ( (a >> i) & 1 ) != 0 ){
            if( is_pow){
                is_pow = false;
                break;
            } else
                is_pow = true;
        }
    }
    if( is_pow)
        printf("it is 2 pow\n");
    else
        printf(" it is not 2 pow\n");
    return 0;
}
