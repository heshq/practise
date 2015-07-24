#include <iostream>
#include <fstream>
#include <vector>

#include "sudoku.h"
#include "solve.h"
#include "timer.h"

using namespace std;

int main( int argc, char **argv)
{
	istream *is = &cin;
	if ( argc > 1) {
		ifstream *ifs = new ifstream;
		ifs->open( argv[ 1]);
		is = ifs;
	};
	Sudoku s;
	float total_time = 0;
	while ( *is >> s) {
		Timer timer;
		vector< Sudoku> answers;
		timer.begin();
		solve( s, answers);
		timer.end();

		bool correct = true;
		for ( auto answer : answers) {
			//cout << endl << answer << endl;
			if ( ! s.check_answer( answer)) {
				correct = false;
				break;
			}
		}
		cout << ( correct
				? "[O] correct. "
				: "[X] wrong.   ");

		cout << ": " << timer.seconds() << " sec.  ";
		cout << answers.size() << " answer(s) found. " << endl;

		total_time += timer.seconds();
	}

	cout << "Total Time : " << total_time << " sec." << endl;

	return 0;
}

