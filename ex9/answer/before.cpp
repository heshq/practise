#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib> // exit()

using namespace std;

#define STACK_CHECK

template< typename T>
void _qsort_inner( T *array, size_t from, size_t to)
{
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
	if ( i > from + 2)
		_qsort_inner( array, from, i - 1);
	if ( i + 1 < to)
		_qsort_inner( array, i, to);
#undef SWAP
}

template< typename T>
void qsort( T *array, size_t size)
{
	_qsort_inner( array, 0, size);
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

