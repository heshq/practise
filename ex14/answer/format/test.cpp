#include <iostream>
#include "format.h"

using namespace std;

int main()
{
    cout << format( "%-1.2f", 1.234f) << endl;
    cout << format( "123456789012345678901234567890\n%s %d", "hello", 1234) << endl;
    //cout << format( "%f,%f,%f", 1.234, 567, 890.1) << endl;
    return 0;
}

