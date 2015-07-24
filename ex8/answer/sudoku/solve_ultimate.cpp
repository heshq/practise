#include "sudoku.h"
#include "solve.h"

using namespace std;

// use global vars to avoid passing params:

Sudoku _s;
vector< Sudoku> *_answers;

struct {
	int l, c;
} _position[ Sudoku::SIZE * Sudoku::SIZE + 1];


void _recursive( int i)
{
	int &l = _position[ i].l;
	int &c = _position[ i].c;
	if ( l >= Sudoku::SIZE)
		_answers->push_back( _s);
	else if ( Sudoku::is_num( _s[ l][ c]))
		_recursive( i + 1);
	else {
		Sudoku::CDDT cddt = _s.get_cddt( l, c);
		for ( char num = 1; num <= Sudoku::SIZE; num ++)
			if ( Sudoku::cddt_get_value( cddt, num)) {
				_s.set_and_check( l, c, num);
				_recursive( i + 1);
				_s.set_and_check( l, c, Sudoku::EMPTY);
			} // if not used
	}
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
	_s.check_all();

	_recursive( 0);
}

