#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // exit()

using namespace std;

#define STACK_CHECK

template< typename T>
void qsort( T *array, size_t size)
{
	struct {
		size_t from, to;
	} stack[ sizeof( void *) * 8];
	int top = 0;
#ifdef STACK_CHECK
	int max_top = 0;
#endif
	stack[ 0].from = 0;
	stack[ 0].to = size;

	while ( top >= 0) {
		// pop:
		size_t from = stack[ top].from;
		size_t to   = stack[ top].to;
		top --;

		// sort:
#define SWAP( a, b) { \
			if ( a != b) { \
				T swap_temp = array[ a]; \
				array[ a] = array[ b]; \
				array[ b] = swap_temp; \
			} \
		}
		T x = array[ from];
		size_t i = to;
		for ( size_t j = to - 1; j > from; j --)
			if ( x < array[ j]) {
				i --;
				SWAP( i, j);
			}
		SWAP( i - 1, from);
#undef SWAP

		// push:
		size_t range_left  = i - 1 - from;
		size_t range_right = to - i;
#define PUSH_LEFT { \
			top ++; \
			stack[ top].from = from; \
			stack[ top].to   = i - 1; \
		}
#define PUSH_RIGHT { \
			top ++; \
			stack[ top].from = i; \
			stack[ top].to   = to; \
		}
		// no need to push segments with no more than 1 element:
		if ( range_left < 2 && range_right < 2)
			continue;
		else if ( range_left < 2) {
			PUSH_RIGHT;
		} else if ( range_right < 2) {
			PUSH_LEFT;
		}
		// when 2 pushes needed, always push longer segment first:
		else if ( range_left <= range_right) {
			PUSH_RIGHT;
			PUSH_LEFT;
		} else {
			PUSH_LEFT;
			PUSH_RIGHT;
		}
#undef PUSH_LEFT
#undef PUSH_RIGHT

#ifdef STACK_CHECK
		if ( top > max_top)
			max_top = top;
#endif
	} // while stack not empty

#ifdef STACK_CHECK
	cout << "stack size     : " << sizeof( stack) / sizeof( stack[ 0]) << endl;
	cout << "max stack used : " << max_top + 1 << endl;
#endif
}

istream *prepare_file( int argc, char **argv)
{
	if ( argc > 0) {
		ifstream *ifs = new ifstream;
		ifs->open( argv[ 1]);
		if ( *ifs)
			return ifs;
		else
			delete ifs;
	}
	return &cin;
}

template< typename T>
T *read_array( istream &is, size_t &size)
{
	vector<T> vec;
	T data;
	while ( is >> data)
		vec.push_back( data);
	size = vec.size();
	T *array = new T[ size];
	for ( size_t i = 0; i < size; i ++)
		array[ i] = vec[ i];
	return array;
}

int main( int argc, char **argv)
{
	istream *is = prepare_file( argc, argv);
	size_t size;
	auto *array = read_array<int>( *is, size);
	qsort( array, size);
	for ( size_t i = 0; i < size; i ++)
		cout << array[ i] << ' ';
	cout << endl;
	delete[] array;
	return 0;
}

