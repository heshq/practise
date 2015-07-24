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

void solve( Sudoku const &original, vector< Sudoku> &answers)
{
	// no need to copy sudoku every time, use just one instance instead:
	Sudoku s( original);

	struct StackData {
		int l, c;
		char num; // number tried for cell[l][c]
	};
	StackData stack[ Sudoku::SIZE * Sudoku::SIZE + 1];

	stack[ 0].num = 0;
	int top = 0;

	// notice l & c for each level in stack never change:
	for ( int l = 0; l < Sudoku::SIZE; l ++)
		for ( int c = 0; c < Sudoku::SIZE; c ++) {
			stack[ top].l = l;
			stack[ top].c = c;
			top ++;
		}
	stack[ Sudoku::SIZE * Sudoku::SIZE].l = Sudoku::SIZE;

	top = 0;
	while ( top >= 0) {
		int &l = stack[ top].l;
		int &c = stack[ top].c;
		char &num = stack[ top].num;

		if ( num == 0)	// enter new stack level:
		{
			if ( l >= Sudoku::SIZE) {
				answers.push_back( s);
				top --;
			} else {
				if ( Sudoku::is_num( s[ l][ c])) {
					stack[ top + 1].num = 0;
					num = Sudoku::SIZE + 1;
					top ++;
				}
				else // if is space, do the loop:
					num = 1;
			}
		} else if ( num <= Sudoku::SIZE) { // the loop:
			s.set( l, c) = Sudoku::EMPTY;
			if ( not_used_in_square( s, Sudoku::square( l, c), num)
					&& not_used_in_column( s, c, num)
					&& not_used_in_line( s, l, num)) {
				s.set( l, c) = num ++;
				stack[ top + 1].num = 0;
				top ++;
			} else
				num ++;
		} else {	// done with this level of stack:
			s.set( l, c) = original[ l][ c];
			top --;
		}
	} // while stack
}


