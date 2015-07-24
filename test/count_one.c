#include <stdio.h>
#include <limits.h>

int main()
{
    unsigned a = 0;
    scanf( "%u",&a);
    int count = 0;
    /*for( int i =0 ; i < CHAR_BIT * sizeof( unsigned); i++){
        if( ( ( a >> i) & 1) != 0){
            count ++;
        }
    }*/
    if( a){
        do {
            count ++;
        } while( a &= a - 1);
    }
    printf( "1 count :%d\n",count);
    return 0;
}
