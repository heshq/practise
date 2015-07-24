#include "sudoku.h"
#include "solve.h"

using namespace std;

// use global vars to avoid passing params:

Sudoku _s;
vector< Sudoku> *_answers;

struct {
	int l, c;
} _position[ Sudoku::SIZE * Sudoku::SIZE + 1];



bool not_used_in_square( int sq, char num)
{
	int square_l = sq / 3 * 3;
	int square_c = sq % 3 * 3;
	for ( int l = square_l; l < square_l + 3; l ++)
		for ( int c = square_c; c < square_c + 3; c ++)
			if ( _s[ l][ c] == num)
				return false;
	return true;
}

bool not_used_in_line( int l, char num)
{
	for ( int c = 0; c < Sudoku::SIZE; c ++)
		if ( _s[ l][ c] == num)
			return false;
	return true;
}

bool not_used_in_column( int c, char num)
{
	for ( int l = 0; l < Sudoku::SIZE; l ++)
		if ( _s[ l][ c] == num)
			return false;
	return true;
}

void _recursive( int i)
{
	int &l = _position[ i].l;
	int &c = _position[ i].c;
	if ( l >= Sudoku::SIZE)
		_answers->push_back( _s);
	else if ( Sudoku::is_num( _s[ l][ c]))
		_recursive( i + 1);
	else for ( char num = 1; num <= Sudoku::SIZE; num ++)
		if ( not_used_in_square( Sudoku::square( l, c), num)
				&& not_used_in_column( c, num)
				&& not_used_in_line( l, num)) {
			_s.set( l, c) = num;
			_recursive( i + 1);
			_s.set( l, c) = Sudoku::EMPTY;
		} // if not used
}

void solve( Sudoku const &s, vector< Sudoku> &answers)
{
	// notice l & c for each level of stack never change:
	int i = 0;
	for ( int l = 0; l < Sudoku::SIZE; l ++)
		for ( int c = 0; c < Sudoku::SIZE; c ++) {
			_position[ i].l = l;
			_position[ i].c = c;
			i ++;
		}
	_position[ Sudoku::SIZE * Sudoku::SIZE].l = Sudoku::SIZE;

	_answers = &answers;
	_s = s;

	_recursive( 0);
}

