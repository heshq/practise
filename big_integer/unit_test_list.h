#ifndef UNIT_TEST_LIST_H
#define UNIT_TEST_LIST_H

void test_add();

struct { char const *name; void (*func)(); } case_list[] = {
	{ "test_add", test_add},
	{ NULL, NULL}
};

#endif
