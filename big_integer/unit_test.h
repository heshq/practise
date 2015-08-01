#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>
#include "big_integer.h"

extern int malloc_failed;
extern int test_case_total;
extern int test_case_failed;

#define CREATE( size)            big_integer_create( size)
#define INIT( bigint, value)     big_integer_init( bigint, value)
#define ASSIGN( target, source)  big_integer_assign( target, source)

#define ADD( left, right)        big_integer_add( left, right)
#define MINUS( left, right)      big_integer_minus( left, right)
#define MULTIPLY( left, right)   big_integer_multiply( left, right)
#define DIVIDE( left, right)     big_integer_divide( left, right)
#define MOD( left, right)        big_integer_mod( left, right)

#define LESS( left,right)            big_integer_less( left, right)
#define LESS_EQUAL( left,right)      big_integer_less_equal( left, right)
#define GREATER( left,right)         big_integer_greater( left, right)
#define GREATER_EQUAL( left,right)   big_integer_greater_equal( left, right)
#define EQUAL( left,right)           big_integer_equal( left, right)
#define NOT_EQUAL( left,right)       big_integer_not_equal( left, right)


#define DESTROY( bigint)    big_integer_destroy( bigint)


#define ASSERT( ASSERTION, msg) if( !( ASSERTION)) { \
    printf( "============assert failed==================\n\
file:%s line:%d function:%s\n\
detail:%s\n",__FILE__,__LINE__,__FUNCTION__,msg);\
    test_case_failed++;\
            }\
            test_case_total++;

#define REGISTER_CASE( case_name) void case_name() 

#endif

