#include <iostream>

using namespace std;

#define SHOW_DETAIL

#ifdef SHOW_DETAIL
	void PRINT_DETAIL( size_t which, unsigned *point, size_t *choice)
	{
		if ( choice[ which] < which)
			PRINT_DETAIL( choice[ which], point, choice);
		cout << point[ which] << ' ';
	}
#else
#	define PRINT_DETAIL( which, point, choice)
#endif

int main()
{
	unsigned size;
	while ( cin >> size) {
		if ( size <= 0)
			continue;

		unsigned point[ size];
		// point[ i] store point in cell i.
		for ( size_t i = 0; i < size; i ++)
			if ( ! ( cin >> point[ i]))
				break;

#ifdef SHOW_DETAIL
		size_t choice[ size];
		size_t which_answer = 0;
#endif

		unsigned score[ size];
		/* score[ i] means the best score one can get
		 * after step into cell i.
		 *
		 * easy to find that:
		 *
		 * score[i] = 
		 * point[i] + max{ score[j] } , where j < i, and point[j] < point[i]
		 * 
		 * or
		 * 
		 * score[i] = point[i] , if no such j found
		 */

		for ( size_t i = 0; i < size; i ++) {
			size_t best;
			bool found = false;
			for ( size_t j = 0; j < i; j ++)
				if ( point[ j] < point[ i])
					if ( ! found || score[ j] > score[ best]) {
						found = true;
						best = j;
					}
			if ( found)
				score[ i] = point[ i] + score[ best];
			else
				score[ i] = point[ i];
#ifdef SHOW_DETAIL
			choice[ i] = found ? best : i;
#endif
		}

		// then the answer should be max{ score[i] }:
		unsigned answer = 0;
		for ( size_t i = 0; i < size; i ++)
			if ( score[ i] > answer) {
				answer = score[ i];
#ifdef SHOW_DETAIL
				which_answer = i;
#endif
			}

		cout << answer << endl;

		PRINT_DETAIL( which_answer, point, choice);
		cout << endl;
	}
	return 0;
}

