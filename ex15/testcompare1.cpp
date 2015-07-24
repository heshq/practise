#include <iomanip>//setprecision
#include <iostream>//cout
#include "compare.h"

using namespace std;

int main()
{
	unsigned char c = 1;
	unsigned short s = 2;
	unsigned i = 3;
	unsigned long l = 4;
	int a = -1;
	float f = 2.0 / 3;
	double d = 2.0 / 3;

	custom_compare::less< unsigned char, int> compare1;
	custom_compare::less< unsigned short, int> compare2;
	custom_compare::less< unsigned, int> compare3;
	custom_compare::less< unsigned long, int> compare4;
	custom_compare::less< int, unsigned char> compare5;
	custom_compare::less< int, unsigned short> compare6;
	custom_compare::less< int, unsigned> compare7;
	custom_compare::less< int, unsigned long> compare8;
	custom_compare::less< float, double> compare9;
	custom_compare::less< double, float> compare10;
	
	cout << ( int)c << "<" << a << " " <<( compare1( c, a) ? "true" : "false")<< endl;
	cout << s << "<" << a << " " << ( compare2( s, a) ? "true" : "false")<< endl;
	cout << i << "<" << a << " " << ( compare3( i, a) ? "true" : "false")<< endl;
	cout << l << "<" << a << " " << ( compare4( l, a) ? "true" : "false")<< endl;
	cout << a << "<" << ( int)c << " " << ( compare5( a, c) ? "true" : "false")<< endl;
	cout << a << "<" << s << " " << ( compare6( a, s) ? "true" : "false")<< endl;
	cout << a << "<" << i << " " << ( compare7( a, i) ? "true" : "false")<< endl;
	cout << a << "<" << l << " " << ( compare8( a, l) ? "true" : "false")<< endl;
	cout << std::setprecision( 20);
	cout << f << "<" << d << " " << ( compare9( f, d) ? "true" : "false")<< endl;
	cout << d << "<" << f << " " << ( compare10( d, f) ? "true" : "false")<< endl;

	custom_compare::less_equal< double, float> compare11;
	cout << d << "<=" << f << " " << ( compare11( d, f) ? "true" : "false")<< endl;
	custom_compare::greater_equal< double, float> compare12;
	cout << d << ">=" << f << " " << ( compare12( d, f) ? "true" : "false")<< endl;
	custom_compare::greater< double, float> compare13;
	cout << d << ">" << f << " " << ( compare13( d, f) ? "true" : "false")<< endl;
	custom_compare::equal< double, float> compare14;
	cout << d << "==" << f << " " << ( compare14( d, f) ? "true" : "false")<< endl;
	return 0;
}
