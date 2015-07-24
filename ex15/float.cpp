#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	float a = 2.0 / 3;
	double b = 2.0 / 3;
    cout << setprecision( 20);
	cout << a << " == " << b << " is "
		<< ( a == b ? "true" : "false") << endl;
	cout << a << " > " << b << " is "
		<< ( a > b ? "true" : "false") << endl;
	return 0;
}
