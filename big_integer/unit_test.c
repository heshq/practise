#include <stdio.h>
#include "unit_test.h"
#include "unit_test_list.h"

int malloc_failed = 0;
int test_case_total = 0;
int test_case_failed = 0;

int main()
{
    int i = 0;
    while( case_list[ i].func != NULL) {
        int last_case_total = test_case_total;
        int last_case_failed = test_case_failed;
        case_list[ i].func();
        printf( "test case [ %s]:%s , total case: %d, failed case:%d\n", 
                case_list[ i].name,
                last_case_failed == test_case_failed ? "PASS":"FAILED",
                test_case_total - last_case_total,
                test_case_failed - last_case_failed);
        i++;
    }
    printf("TEST %s\n", test_case_failed == 0 ? "PASS":"FAILED");
    return 0;
}
