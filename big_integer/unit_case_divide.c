#include "unit_test.h"

REGISTER_CASE( test_divide)
{
    BigInteger *left    = CREATE( 2); 
    BigInteger *right   = CREATE( 2); 
    BigInteger *result  = CREATE( 2); 

    //same symbol
    INIT( left,   "21");
    INIT( right,  "7");
    INIT( result, "3");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"21 / 7 = 3 failed");

    INIT( left,   "-21");
    INIT( right,  "-3");
    INIT( result, "7");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"( -21) / ( -3) = 7 failed");

    //oppsite symbol
    INIT( left,   "-21");
    INIT( right,  "7");
    INIT( result, "-3");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"-21 / 7 = ( -3) failed");

    INIT( left,   "21");
    INIT( right,  "-7");
    INIT( result, "-3");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"21 / ( -7) = ( -3) failed");

    //DIVIDE with zero
    INIT( left,   "21");
    INIT( right,  "0");
    ASSIGN( result, DIVIDE( left, right));
    ASSERT( result->is_nan,"21 / 0 = nan failed");

    INIT( left,   "21");
    INIT( right,  "-0");
    ASSIGN( result, DIVIDE( left, right));
    ASSERT( result->is_nan,"21 / ( -0) = nan failed");

    INIT( left,   "-21");
    INIT( right,  "0");
    ASSIGN( result, DIVIDE( left, right));
    ASSERT( result->is_nan,"( -21) / 0 = nan failed");

    INIT( left,   "-21");
    INIT( right,  "-0");
    ASSIGN( result, DIVIDE( left, right));
    ASSERT( result->is_nan,"( -21) / ( -0) = nan failed");

    INIT( left,   "100000");
    INIT( right,  "100");
    INIT( result, "1000");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"100000 / 100 = 1000 failed");

    INIT( left,   "-100000");
    INIT( right,  "100");
    INIT( result, "-1000");
    ASSERT( EQUAL( result, DIVIDE( left, right)),"( -100000) / 100 = ( -1000) failed");

    DESTROY( left);
    DESTROY( right);
    DESTROY( result);
}


