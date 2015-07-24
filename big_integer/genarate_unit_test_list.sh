#!/bin/bash

(
echo "#ifndef UNIT_TEST_LIST_H"
echo "#define UNIT_TEST_LIST_H"
echo 
for f in unit_case_*.c
do
	grep REGISTER_CASE $f | grep -Po '\(.*\)' | grep -Po '[_a-zA-Z0-9]+' |
	while read line
	do
		echo "void ${line}();"
	done
done
echo
echo "struct { char const *name; void (*func)(); } case_list[] = {"
for f in unit_case_*.c
do
	grep REGISTER_CASE $f | grep -Po '\(.*\)' | grep -Po '[_a-zA-Z0-9]+' |
	while read line
	do
		echo "	{ \"${line}\", ${line}},"
	done
done
echo "	{ NULL, NULL}"
echo "};"
echo
echo "#endif"
) > unit_test_list.h


