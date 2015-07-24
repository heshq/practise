#include <iostream>
#include "metering_system.h"

using namespace std;
using namespace metering_system;
int main()
{
    Metering< BS,int> bs1( 2);
    Metering< BS,int> bs2( 4);
    Metering< BS,int> bs3( 0);
    Metering< IS,int> is1( 2);
    Metering< IS,int> is2( 4);
    
    bs3 = bs1 + bs2;
    bs3 = bs1 + 1;
    bs3 = bs1 - bs2;
    bs3 = bs1 - 1;
    bs3 = is1( MS::is)*2;
    cout << "bs1 + 1 = " << ( bs1 + 1)( MS::bs) << endl;
    cout << "bs1 + bs2 = " <<( bs1 + bs2)( MS::bs) << endl;
    //cout << ( bs1 + is1)( MS::bs) << endl;
    cout << "bs1 - 1 = " <<( bs1 - 1)( MS::bs) << endl;
    cout << "bs1 - bs2 = " <<( bs1 - bs2)( MS::bs) << endl;
    //cout << ( bs1 - is1)( MS::bs) << endl;
    cout << "bs1( MS::bs)/2 = " << bs1( MS::bs)/2 << endl;
    cout << "bs1( MS::bs)*2 = " << bs1( MS::bs)*2 << endl;
    
    cout << bs1( MS::bs) << " <  " << bs2( MS::bs) << ( bs1 < bs2 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " <= " << bs2( MS::bs) << ( bs1 <= bs2 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " >  " << bs2( MS::bs) << ( bs1 > bs2 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " >= " << bs2( MS::bs) << ( bs1 >= bs2 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " == " << bs2( MS::bs) << ( bs1 == bs2 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " != " << bs2( MS::bs) << ( bs1 != bs2 ? " true" : " false") << endl;
    
    cout << bs1( MS::bs) << " <  " << 6 << ( bs1 < 6 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " <= " << 6 << ( bs1 <= 6 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " >  " << 6 << ( bs1 > 6 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " >= " << 6 << ( bs1 >= 6 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " == " << 6 << ( bs1 == 6 ? " true" : " false") << endl;
    cout << bs1( MS::bs) << " != " << 6 << ( bs1 != 6 ? " true" : " false") << endl;
    
    //cout << bs1( MS::bs) << " <  " << is1( MS::is) << ( bs1 < is1 ? " true" : " false") << endl;
    //cout << bs1( MS::bs) << " <= " << is1( MS::is) << ( bs1 <= is1 ? " true" : " false") << endl;
    //cout << bs1( MS::bs) << " >  " << is1( MS::is) << ( bs1 > is1 ? " true" : " false") << endl;
    //cout << bs1( MS::bs) << " >= " << is1( MS::is) << ( bs1 >= is1 ? " true" : " false") << endl;
    //cout << bs1( MS::bs) << " == " << is1( MS::is) << ( bs1 == is1 ? " true" : " false") << endl;
    //cout << bs1( MS::bs) << " != " << is1( MS::is) << ( bs1 != is1 ? " true" : " false") << endl;
    return 0;
}
