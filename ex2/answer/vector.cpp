#include <iostream>
#include <array>
#include <initializer_list>

using namespace std;

//#define SHOW_TRACE

#ifdef SHOW_TRACE
	struct Trace {
		static unsigned level;
		void indent()
		{
			for ( unsigned i = 0; i < level; i ++)
				cerr << "  ";
		}
		Trace( char const *func, char const *msg)
		{
			++ level;
			indent();
			cerr << func << ": " << msg << endl;
		}
		~Trace()
		{
			if ( level)
				level --;
		}
		void trace_line( char const *func, int line, char const *msg)
		{
			indent();
			cerr << func << '@' << line << ": " << msg << endl;
		}
	};
	unsigned Trace::level = 0;
#	define TRACE( msg)	Trace __trace_guard( __func__, msg)
#	define TRACE_LINE( msg)	__trace_guard.trace_line( __func__, __LINE__, msg)
#else
#	define TRACE( msg)
#	define TRACE_LINE( msg)
#endif

template< typename T, unsigned N>
class Vec : protected array< T, N>
{
	public:
		using array< T, N>::operator[];
		using array< T, N>::at;
		using array< T, N>::fill;

		Vec() { TRACE( "default constructor");}

		Vec( initializer_list< T> const &list)
		{
			TRACE( "list constructor");
			size_t i = 0;
			for ( typename initializer_list<T>::iterator it = list.begin();
					i < N && it != list.end();
					++ i, ++ it
			)
				at( i) = *it;
		}

		// copy from array:
		Vec( array< T, N> const &arr)
			: array< T, N>( arr)
		{
			TRACE( "copy from array");
		}

		// copy from Vec:
		Vec( Vec< T, N> const &another)
			: array< T, N>( another)
		{
			TRACE( "copy from Vec");
		}

		Vec operator+( Vec< T, N> const &another) const
		{
			TRACE( "");
			Vec result( *this);
			for ( size_t i = 0; i < N; i ++)
				result[ i] += another[ i];
			return result;
		}

		Vec operator-( Vec< T, N> const &another) const
		{
			TRACE( "");
			Vec result( *this);
			for ( size_t i = 0; i < N; i ++)
				result[ i] -= another[ i];
			return result;
		}

		Vec const &operator+=( Vec< T, N> const &another)
		{
			TRACE( "");
			for ( size_t i = 0; i < N; i ++)
				at( i) += another[ i];
			return *this;
		}

		Vec const &operator-=( Vec< T, N> const &another)
		{
			TRACE( "");
			for ( size_t i = 0; i < N; i ++)
				at( i) -= another[ i];
			return *this;
		}

		Vec const &operator=( Vec< T, N> const &another)
		{
			TRACE( "");
			for ( size_t i = 0; i < N; i ++)
				at( i) = another[ i];
			return *this;
		}

/*		template< typename T2>
		Vec operator*( T2 number)
		{
			TRACE( "");
			Vec result( *this);
			for ( size_t i = 0; i < N; i ++)
				result[ i] *= number;
			return result;
		}*/

		template< typename T2>
		Vec const &operator*= ( T2 number)
		{
			TRACE( "");
			for ( size_t i = 0; i < N; i ++)
				at( i) *= number;
			return *this;
		}

};

template< typename T, typename T2, unsigned N>
Vec< T, N> operator*( Vec< T, N> const &vec, T2 number)
{
	TRACE( "");
	Vec< T, N> result( vec);
	for ( size_t i = 0; i < N; i ++)
		result[ i] *= number;
	return result;
}

template< typename T, typename T2, unsigned N>
Vec< T, N> operator*( T2 number, Vec< T, N> const &vec)
{
	return vec * number;
}

template< typename T, unsigned N>
ostream &operator<<( ostream &os, Vec< T, N> const &vec)
{
	cout << '(';
	if ( N > 0)
		os << vec[ 0];
	for ( size_t i = 1; i < N; i ++)
		os << ',' << vec[ i];
	os << ')';
	return os;
}

int main()
{
	typedef int Number;

	TRACE( "");
	Vec< Number, 4> a { 2, 4, 6, 5592402};
	TRACE_LINE( "");

	cout << fixed;
	cout << 0.5 * a << endl;

	Vec< Number, 4> b;
	TRACE_LINE( "");
	b[ 0] = 5; b[ 1] = 7; b[ 2] = 9; b[ 3] = 11;

	Vec< Number, 4> &&c( a * 3 + b);
	TRACE_LINE( "");

	cout << c << endl;
	return 0;
}

