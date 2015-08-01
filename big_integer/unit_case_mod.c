#include "unit_test.h"

REGISTER_CASE( test_mod)
{
    BigInteger *left    = CREATE( 2); 
    BigInteger *right   = CREATE( 2); 
    BigInteger *result  = CREATE( 2); 

    //same symbol
    INIT( left,   "10");
    INIT( right,  "3");
    INIT( result, "1");
    ASSERT( EQUAL( result, MOD( left, right)),"10 % 3 = 1 failed");

    INIT( left,   "-10");
    INIT( right,  "-3");
    INIT( result, "1");
    ASSERT( EQUAL( result, MOD( left, right)),"( -10) % ( -3) = 1 failed");

    //oppsite symbol
    INIT( left,   "-10");
    INIT( right,  "3");
    INIT( result, "-1");
    ASSERT( EQUAL( result, MOD( left, right)),"-10 % 3 = ( -1) failed");

    INIT( left,   "10");
    INIT( right,  "-3");
    INIT( result, "-1");
    ASSERT( EQUAL( result, MOD( left, right)),"10 % ( -3) = ( -1) failed");

    //MOD with zero
    INIT( left,   "21");
    INIT( right,  "0");
    ASSIGN( result, MOD( left, right));
    ASSERT( result->is_nan,"21 % 0 = nan failed");

    INIT( left,   "21");
    INIT( right,  "-0");
    ASSIGN( result, MOD( left, right));
    ASSERT( result->is_nan,"21 % ( -0) = nan failed");

    INIT( left,   "-21");
    INIT( right,  "0");
    ASSIGN( result, MOD( left, right));
    ASSERT( result->is_nan,"( -21) % 0 = nan failed");

    INIT( left,   "-21");
    INIT( right,  "-0");
    ASSIGN( result, MOD( left, right));
    ASSERT( result->is_nan,"( -21) % ( -0) = nan failed");

    INIT( left,   "100000");
    INIT( right,  "100");
    INIT( result, "0");
    ASSERT( EQUAL( result, MOD( left, right)),"100000 % 100 = 10 failed");

    INIT( left,   "-100000");
    INIT( right,  "100");
    INIT( result, "-0");
    ASSERT( EQUAL( result, MOD( left, right)),"( -100000) % 100 = ( -10) failed");

    DESTROY( left);
    DESTROY( right);
    DESTROY( result);
}


