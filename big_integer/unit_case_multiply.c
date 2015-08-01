#include "unit_test.h"

REGISTER_CASE( test_multiply)
{
    BigInteger *left    = CREATE( 2); 
    BigInteger *right   = CREATE( 2); 
    BigInteger *result  = CREATE( 4); 

    //same symbol
    INIT( left,   "3");
    INIT( right,  "6");
    INIT( result, "18");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"3 * 6 = 18 failed");
    INIT( left,   "-3");
    INIT( right,  "-6");
    INIT( result, "18");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"( -3) * ( -6) = ( -18) failed");

    //oppsite symbol
    INIT( left,   "-3");
    INIT( right,  "6");
    INIT( result, "-18");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"( -3) * 6 = -18 failed");
    INIT( left,   "3");
    INIT( right,  "-6");
    INIT( result, "-18");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"3 * ( -6) = ( -18) failed");
    INIT( left,   "0");
    INIT( right,  "-0");
    INIT( result, "0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"0 * ( -0) = 0 failed");
    INIT( left,   "-0");
    INIT( right,  "0");
    INIT( result, "0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"( -0) * 0 = 0 failed");

    //MULTIPLY with zero
    INIT( left,   "21");
    INIT( right,  "0");
    INIT( result, "0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"21 * 0 = 0 failed");
    INIT( left,   "21");
    INIT( right,  "-0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"21 * ( -0) = 0 failed");
    INIT( left,   "21");
    INIT( right,  "0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"21 * 0 = 0 failed");
    INIT( left,   "-21");
    INIT( right,  "0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"( -21) * 0 = 0 failed");
    INIT( left,   "-21");
    INIT( right,  "-0");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"( -21) * ( -0) = 0 failed");

    INIT( left,   "1000");
    INIT( right,  "100");
    INIT( result, "100000");
    ASSERT( EQUAL( result, MULTIPLY( left, right)),"1000 * 100 = 100000 failed");

    DESTROY( left);
    DESTROY( right);
    DESTROY( result);
}


