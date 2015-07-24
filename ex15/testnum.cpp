#include <cfloat>
#include <climits>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    cout << setprecision( 20);
    float f = 4.0 / 3;
    cout << ( int)( f) << endl; // 1
    cout << ( int)( f * 10 ) << endl; //13
    int i = INT_MAX;
    cout << INT_MAX << "-----" << ( float)i << endl;
    float d = 8589934593 ;
    cout << d << "-----" << ( int)d <<endl;
    cout << "FLT_DIG:" << FLT_DIG << " DBL_DIG:" << DBL_DIG << endl;
    cout << "FLT_MAX:" << FLT_MAX << " DBL_MAX:" << DBL_MAX << endl;
    return 0;
}
