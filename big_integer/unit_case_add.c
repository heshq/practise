#include "unit_test.h"

REGISTER_CASE( test_add)
{
    BigInteger *left    = CREATE( 2); 
    BigInteger *right   = CREATE( 2); 
    BigInteger *result  = CREATE( 2); 

    //same symbol
    INIT( left,   "21");
    INIT( right,  "21");
    INIT( result, "42");
    ASSERT( EQUAL( result, ADD( left, right)),"21 + 21 = 42 failed");

    INIT( left,   "-21");
    INIT( right,  "-21");
    INIT( result, "-42");
    ASSERT( EQUAL( result, ADD( left, right)),"( -21) + ( -21) = ( -42) failed");

    //oppsite symbol
    INIT( left,   "-21");
    INIT( right,  "42");
    INIT( result, "21");
    ASSERT( EQUAL( result, ADD( left, right)),"-21 + 42 = 21 failed");

    INIT( left,   "21");
    INIT( right,  "-42");
    INIT( result, "-21");
    ASSERT( EQUAL( result, ADD( left, right)),"21 + ( -42) = ( -21) failed");

    INIT( left,   "0");
    INIT( right,  "-0");
    INIT( result, "0");
    ASSERT( EQUAL( result, ADD( left, right)),"0 + ( -0) = 0 failed");

    //add with zero
    INIT( left,   "21");
    INIT( right,  "0");
    INIT( result, "21");
    ASSERT( EQUAL( result, ADD( left, right)),"21 + 0 = 21 failed");

    INIT( left,   "21");
    INIT( right,  "-0");
    INIT( result, "21");
    ASSERT( EQUAL( result, ADD( left, right)),"21 + ( -0) = 21 failed");

    INIT( left,   "-21");
    INIT( right,  "0");
    INIT( result, "-21");
    ASSERT( EQUAL( result, ADD( left, right)),"( -21) + 0 = ( -21) failed");

    INIT( left,   "-21");
    INIT( right,  "0");
    INIT( result, "-21");
    ASSERT( EQUAL( result, ADD( left, right)),"( -21) + 0 = ( -21) failed");

    INIT( left,   "9999");
    INIT( right,  "2");
    INIT( result, "10001");
    ASSERT( EQUAL( result, ADD( left, right)),"9999 + 2 = 10001 failed");

    DESTROY( left);
    DESTROY( right);
    DESTROY( result);
}


