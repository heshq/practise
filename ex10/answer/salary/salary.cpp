#include <cstring>	// memset()

#include "salary.h"

Salary::Salary( size_t max_employee_id)
	: size( _size)
{
	// make sure _size is power of 2, and no less than acutal employee number:
	for ( _size = 1; _size < max_employee_id; _size <<= 1)
		;
	size_t tree_size = _size * 2 - 1;
	_record = new int[ tree_size];
	memset( _record, 0, sizeof( int) * tree_size);
}

Salary::~Salary()
{
	delete[] _record;
}

void
Salary::rise( size_t from, size_t to, int how_much)
{
	// Boss He is a man with style,
	// we are not sure if he will provide the range
	// in normal people's order:
	if ( from > to) {
		size_t swap_temp = from;
		from = to;
		to = swap_temp;
	}

	// start _rise() recurse with root node:
	NodeInfo &&root = _root();
	_rise( root, from, to, how_much);
}

void
Salary::_rise( NodeInfo &node, size_t change_from, size_t change_to, int how_much)
{
	// if current node represent a segment exactly equal
	// to the range Boss He specified,
	// then just record the salary changeing into it and return.
	if ( change_from == node.segment_begin && change_to == node.segment_end)
		_record[ node.idx] += how_much;

	// if not, split the segment in half,
	// divide the range into these 2 smaller segments:
	else {
		NodeInfo &&left = node.left_child();
		NodeInfo &&right = node.right_child();

		if ( change_to <= left.segment_end)
			_rise( left, change_from, change_to, how_much);
		else if ( change_from >= right.segment_begin)
			_rise( right, change_from, change_to, how_much);
		else {
			_rise( left, change_from, left.segment_end, how_much);
			_rise( right, right.segment_begin, change_to, how_much);
		}
	}
}

int
Salary::query( size_t employee_id)
{
	NodeInfo node = _root();
	int salary = INITIAL_SALARY;
	while ( ! node.is_leaf()) {
		salary += _record[ node.idx];
		if ( employee_id <= node.middle())
			node = node.left_child();
		else
			node = node.right_child();
	}
	salary += _record[ node.idx];
	return salary;
}

