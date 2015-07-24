#include <stdio.h>
#include <stdbool.h>

int main()
{
    int v = true;
    printf("size is %zu\n", sizeof( v));
    unsigned long long u = 0xffffffffff00LLU;
    printf("int %d, ull %llu,bool & ull %llu\n", v, u, (v)&u); 
    return 0;
}
