#include "sudoku.h"
#include "solve.h"

using namespace std;

bool not_used_in_square( Sudoku const &s, int sq, char num)
{
	int square_l = sq / 3 * 3;
	int square_c = sq % 3 * 3;
	for ( int l = square_l; l < square_l + 3; l ++)
		for ( int c = square_c; c < square_c + 3; c ++)
			if ( s[ l][ c] == num)
				return false;
	return true;
}

bool not_used_in_line( Sudoku const &s, int l, char num)
{
	for ( int c = 0; c < Sudoku::SIZE; c ++)
		if ( s[ l][ c] == num)
			return false;
	return true;
}

bool not_used_in_column( Sudoku const &s, int c, char num)
{
	for ( int l = 0; l < Sudoku::SIZE; l ++)
		if ( s[ l][ c] == num)
			return false;
	return true;
}

void _recursive( Sudoku const &s, vector< Sudoku> &answers, int l, int c)
{
	if ( l >= Sudoku::SIZE) {
		answers.push_back( s);
		return;
	} else {
		int next_l, next_c;
		if ( c + 1 >= Sudoku::SIZE) {
			next_l = l + 1;
			next_c = 0;
		} else {
			next_l = l;
			next_c = c + 1;
		}
		if ( Sudoku::is_num( s[ l][ c]))
			_recursive( s, answers, next_l, next_c);
		else {
			Sudoku new_s( s);
			for ( char num = 1; num <= Sudoku::SIZE; num ++)
				if ( not_used_in_square( s, Sudoku::square( l, c), num)
						&& not_used_in_column( s, c, num)
						&& not_used_in_line( s, l, num)) {
					new_s.set( l, c) = num;
					_recursive( new_s, answers, next_l, next_c);
					new_s.set( l, c) = Sudoku::EMPTY;
				} // if not used
		} // if space
	} // if not finished
}

void solve( Sudoku const &s, vector< Sudoku> &answers)
{
	_recursive( s, answers, 0, 0);
}

