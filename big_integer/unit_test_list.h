#ifndef UNIT_TEST_LIST_H
#define UNIT_TEST_LIST_H

void test_add();
void test_divide();
void test_equal();
void test_greater();
void test_greater_equal();
void test_less();
void test_less_equal();
void test_minus();
void test_mod();
void test_multiply();
void test_not_equal();

struct { char const *name; void (*func)(); } case_list[] = {
	{ "test_add", test_add},
	{ "test_divide", test_divide},
	{ "test_equal", test_equal},
	{ "test_greater", test_greater},
	{ "test_greater_equal", test_greater_equal},
	{ "test_less", test_less},
	{ "test_less_equal", test_less_equal},
	{ "test_minus", test_minus},
	{ "test_mod", test_mod},
	{ "test_multiply", test_multiply},
	{ "test_not_equal", test_not_equal},
	{ NULL, NULL}
};

#endif
