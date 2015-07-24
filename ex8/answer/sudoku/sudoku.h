#ifndef _SUDOKU_H
#define _SUDOKU_H

#include <iostream>
#include <array>

class Sudoku {
	public:
		static char const EMPTY = 0;
		static int const SIZE = 9;
		
		typedef std::array< char, SIZE> Line;
		typedef unsigned short CDDT;	// list of candidates

		static inline bool is_num( char cell)
		{
			return cell >= 1 && cell <= 9;
		}
		static inline int square( int l, int c)
		{
			/*
			 * split whole board into squares as:
			 * 	000111222
			 * 	000111222
			 * 	000111222
			 * 	333444555
			 * 	333444555
			 * 	333444555
			 * 	666777888
			 * 	666777888
			 * 	666777888
			 */
			return l / 3 * 3 + c / 3;
		}
		static inline void cddt_set_value( CDDT &cddt, int val, bool available)
		{
			CDDT mask = 1 << val;
			if ( available)
				cddt |= mask;
			else
				cddt &= ~mask;
		}
		static inline bool cddt_get_value( CDDT const &cddt, int val)
		{
			CDDT mask = 1 << val;
			return ( cddt & mask) > 0;
		}

	private:
		std::array< Line, SIZE> _cells;
		bool _checked;
		unsigned _spaces;
		std::array< CDDT, SIZE>
			_ln_cddt, _cl_cddt, _sq_cddt;
		// candidates for each line, column, 3*3 square

	public:
		bool const &checked;
		unsigned &spaces;

		Sudoku();
		Sudoku( Sudoku const &another);

		Sudoku const &operator=( Sudoku const &another);
		Line const &operator[]( int idx) const;

		char &set( int l, int c);

		void set_and_check( int l, int c, char val);
		// IMPORTANT: 	only valid candidate or space 
		// 		can be set by set_and_check() !!

		CDDT get_cddt( int l, int c) const;
		
		bool check_all();	// make cddts & spaces valid

		bool check_answer( Sudoku &) const;
};

std::istream &operator>>( std::istream &is, Sudoku &s);
std::ostream &operator<<( std::ostream &os, Sudoku const &s);

#endif


