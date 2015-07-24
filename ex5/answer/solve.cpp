#include <iostream>
#include <fstream>

#include "map.h"
#include "timer.h"

using namespace std;

#define USE_TIMER
//#define DEBUG

// assuming column number less than 32
bool solve( SwitchMap const &map, Map &result)
{
	unsigned range = ( 1 << map.columns) - 1;
	for ( unsigned solution = 0; solution <= range; solution ++) {
		SwitchMap test_map( map);
		result.clear();

		// apply solution into first line:
		for ( size_t c = 0; c < map.columns; c ++)
			if ( solution & ( 1 << c)) {
				result[ 0][ c] = true;
				test_map.turn( 0, c);
			}

		// then infer lines by the line above it:
		for ( size_t l = 1; l < map.lines; l ++)
			for ( size_t c = 0; c < map.columns; c ++)
				if ( test_map[ l - 1][ c]) {
					result[ l][ c] = true;
					test_map.turn( l, c);
				}

#ifdef DEBUG		
		cerr << "SOLUTION " << solution << ":" << endl;
		cerr << " map:" << test_map;
		cerr << " result:" << result;
#endif
		if ( test_map.is_line_clear( map.lines - 1))
			return true;
	}
	return false;
}

int main( int argc, char **argv)
{
	ifstream ifs;
	if ( argc == 2)
		ifs.open( argv[ 1], ifstream::in);
	istream &is( ifs.is_open() ? ifs: cin);

	size_t l, c;
	while ( is >> l >> c) {
#ifdef USE_TIMER
		Timer timer;
#endif
		SwitchMap map( l, c);
		is >> map;
		Map result( l, c);
		if ( ! solve( map, result)) {
			cerr << "Cannot find solution !!!" << endl;
			result.clear();
		}
		cout << result;
	}
	return 0;
}

