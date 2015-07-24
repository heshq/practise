#include "unit_test.h"

int add( int left, int right)
{
    return left + right;
}

REGISTER_CASE( test_add)
{
    ASSERT( add( 1, 2) == 3," add(1, 2)==3 failed");
    ASSERT( add( 1, 2) == 4," add(1, 2)==4 failed");
}


