#include "unit_test.h"

REGISTER_CASE( test_equal)
{
    BigInteger *left    = CREATE( 6); 
    BigInteger *right   = CREATE( 6); 

    //same symbol
    INIT( left,   "21");
    INIT( right,  "21");
    ASSERT( EQUAL( left, right),"21 == 21 failed");

    INIT( left,   "-21");
    INIT( right,  "-21");
    ASSERT( EQUAL( left, right),"( -21) == ( -21) failed");

    INIT( left,   "21");
    INIT( right,  "1");
    ASSERT( !EQUAL( left, right),"21 == 1 failed");

    INIT( left,   "-21");
    INIT( right,  "-1");
    ASSERT( !EQUAL( left, right),"( -21) == ( -1) failed");

    //oppsite symbol
    INIT( left,   "-21");
    INIT( right,  "42");
    ASSERT( !EQUAL( left, right),"-21 == 42 failed");

    INIT( left,   "21");
    INIT( right,  "-42");
    ASSERT( !EQUAL( left, right),"21 == ( -42) failed");

    INIT( left,   "0");
    INIT( right,  "-0");
    ASSERT( EQUAL( left, right),"0 == ( -0) failed");

    INIT( left,   "-0");
    INIT( right,  "0");
    ASSERT( EQUAL( left, right),"( -0) == 0 failed");

    //EQUAL with zero
    INIT( left,   "21");
    INIT( right,  "0");
    ASSERT( !EQUAL( left, right),"21 == 0 failed");

    INIT( left,   "21");
    INIT( right,  "-0");
    ASSERT( !EQUAL( left, right),"21 == ( -0) failed");

    INIT( left,   "-21");
    INIT( right,  "0");
    ASSERT( !EQUAL( left, right),"( -21) == 0 failed");

    INIT( left,   "-21");
    INIT( right,  "-0");
    ASSERT( !EQUAL( left, right),"( -21) == -0 failed");

    INIT( left,   "10000000");
    INIT( right,  "1000000000000");
    ASSERT( !EQUAL( left, right),"10000000 == 100000000000 failed");

    left->is_inf = 1;
    ASSERT( !EQUAL( left, right),"inf == 100000000000 failed");

    left->is_nan = 1;
    ASSERT( !EQUAL( left, right),"nan == 100000000000 failed");

    left->is_inf = 0;
    left->is_nan = 0;

    right->is_inf = 1;
    ASSERT( !EQUAL( left, right),"10000000 == inf failed");

    right->is_nan = 1;
    ASSERT( !EQUAL( left, right),"10000000 == nan failed");

    right->is_inf = 1;
    right->is_nan = 0;
    left->is_inf = 1;
    left->is_nan = 0;
    ASSERT( !EQUAL( left, right),"inf == inf failed");

    right->is_inf = 0;
    right->is_nan = 1;
    left->is_inf = 1;
    left->is_nan = 0;
    ASSERT( !EQUAL( left, right),"inf == nan failed");

    right->is_inf = 1;
    right->is_nan = 0;
    left->is_inf = 0;
    left->is_nan = 1;
    ASSERT( !EQUAL( left, right),"nan == inf failed");

    right->is_inf = 0;
    right->is_nan = 1;
    left->is_inf = 0;
    left->is_nan = 1;
    ASSERT( !EQUAL( left, right),"nan == inf failed");

    DESTROY( left);
    DESTROY( right);
}


