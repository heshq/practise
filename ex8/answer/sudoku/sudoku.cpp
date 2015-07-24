
#include "sudoku.h"

Sudoku::Sudoku() :
	_checked( false),
	checked( _checked),
	spaces( _spaces)
{
}

Sudoku::Sudoku( Sudoku const &s) :
	_cells( s._cells),
	_checked( s.checked),
	_spaces( s._spaces),
	_ln_cddt( s._ln_cddt),
	_cl_cddt( s._cl_cddt),
	_sq_cddt( s._sq_cddt),
	checked( _checked),
	spaces( _spaces)
{
}

Sudoku const &
Sudoku::operator=( Sudoku const &s)
{
	_cells = s._cells;
	_checked = s._checked;
	if ( checked) {
		_ln_cddt = s._ln_cddt;
		_cl_cddt = s._cl_cddt;
		_sq_cddt = s._sq_cddt;
		_spaces = s._spaces;
	}
	return *this;
}

Sudoku::Line const &
Sudoku::operator[]( int idx) const
{
	return _cells[ idx];
}

char &
Sudoku::set( int l, int c)
{
	_checked = false;
	return _cells[ l][ c];
}

void
Sudoku::set_and_check( int l, int c, char val)
{
	char &cell = _cells[ l][ c];
	int sq = square( l, c);
	if ( is_num( cell)) {
		cddt_set_value( _ln_cddt[ l], cell, true);
		cddt_set_value( _cl_cddt[ c], cell, true);
		cddt_set_value( _sq_cddt[ sq], cell, true);
		if ( is_num( val)) {
			cddt_set_value( _ln_cddt[ l], val, false);
			cddt_set_value( _cl_cddt[ c], val, false);
			cddt_set_value( _sq_cddt[ sq], val, false);
		} else
			_spaces ++;
	} else if ( is_num( val)) {
		cddt_set_value( _ln_cddt[ l], val, false);
		cddt_set_value( _cl_cddt[ c], val, false);
		cddt_set_value( _sq_cddt[ sq], val, false);
		_spaces --;
	}
	cell = val;
}

Sudoku::CDDT
Sudoku::get_cddt( int l, int c) const
{
	int sq = square( l, c);
	return _ln_cddt[ l] & _cl_cddt[ c] & _sq_cddt[ sq];
}

bool
Sudoku::check_all()
{
	_ln_cddt.fill( CDDT( -1));
	_cl_cddt.fill( CDDT( -1));
	_sq_cddt.fill( CDDT( -1));
	_spaces = 0;
	for ( int l = 0; l < SIZE; l ++)
		for ( int c = 0; c < SIZE; c ++) {
			char &cell = _cells[ l][ c];
			if ( is_num( cell)) {
				CDDT cddt = get_cddt( l, c);
				if ( ! cddt_get_value( cddt, cell))
					return _checked = false;
				cddt_set_value( _ln_cddt[ l], cell, false);
				cddt_set_value( _cl_cddt[ c], cell, false);
				cddt_set_value( _sq_cddt[ square( l, c)], cell, false);
			} else
				_spaces ++;
		}
	return _checked = true;
}

bool
Sudoku::check_answer( Sudoku &answer) const
{
	if ( ! answer.check_all() || answer.spaces > 0)
		return false;
	for ( int l = 0; l < SIZE; l ++)
		for ( int c = 0; c < SIZE; c ++)
			if ( is_num( _cells[ l][ c]))
				if ( _cells[ l][ c] != answer._cells[ l][ c])
					return false;
	return true;
}

std::istream &
operator>>( std::istream &is, Sudoku &s)
{
	for ( int l = 0; l < Sudoku::SIZE; l ++)
		for ( int c = 0; c < Sudoku::SIZE; c ++) {
			char ch;
REDO:
			if ( is >> ch) {
				if ( ch == ' ' || ch == '-')
					s.set( l, c) = Sudoku::EMPTY;
				else if ( ch >= '1' && ch <= '9')
					s.set( l, c) = ch - '0';
				else
					goto REDO;
			} else
				return is;
		}
	return is;
}

std::ostream &operator<<( std::ostream &os, Sudoku const &s)
{
	for ( int l = 0; l < Sudoku::SIZE; l ++) {
		for ( int c = 0; c < Sudoku::SIZE; c ++)
			if ( Sudoku::is_num( s[ l][ c]))
				os << int( s[ l][ c]);
			else
				os << ' ';
		os << std::endl;
	}
	return os;
}

