#ifndef UNIT_TEST_H
#define UNIT_TEST_H

#include <stdio.h>

extern int test_case_total;
extern int test_case_failed;

#define ASSERT( ASSERTION, msg) if( !( ASSERTION)) { \
    printf( "============assert failed==================\n\
file:%s line:%d function:%s\n\
detail:%s\n",__FILE__,__LINE__,__FUNCTION__,msg);\
    test_case_failed++;\
            }\
            test_case_total++;

#define REGISTER_CASE( case_name) void case_name() 

#endif

