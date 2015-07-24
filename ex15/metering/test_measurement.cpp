#include <iostream>
#include <type_traits>
#include "measurement.h"

struct BigNumber{
    int value = 0;
    BigNumber( int number) : value( number){}
    BigNumber operator+( BigNumber other)
    {
        BigNumber result( value + other.value);
        return result;
    }
    BigNumber operator=( BigNumber number)
    {
        value = number.value;
        return *this;
    }
};

int main()
{
    using namespace std;
    using namespace measurement;

    Number< Meter, int> int_mtr_1( 1000);
    Number< Meter, int> int_mtr_2( 10);
    Number< Meter, int> const int_mtr_3( 10);
    int_mtr_3.as< Meter>();
    //int_mtr_3 += int_mtr_2;
    
    int_mtr_1 = int_mtr_1 + int_mtr_2;
    int_mtr_1 = int_mtr_1 - int_mtr_2;
    int_mtr_1 += int_mtr_2;
    ++int_mtr_2;
    --int_mtr_2;
    int_mtr_2++;
    int_mtr_2--;
    Number< KiloMeter, int> int_klmtr( 10);//for test error
    //int_klmtr + int_mtr_1;//compile error
    Number< Meter, float> flt_mtr( 3.0f);
    Number< Meter, BigNumber> bgnbr_mtr_1( 5);
    Number< Meter, BigNumber> bgnbr_mtr_2( 15);
    Number< Meter, BigNumber> bgnbr_mtr_3( 5);
    int_mtr_2 = int_mtr_1 + int_mtr_2;
    cout << "int_mtr_2 = i1 + int_mtr_2  " << int_mtr_2._value << endl;
    int_mtr_2 = int_mtr_1 - int_mtr_2;
    cout << "int_mtr_2 = int_mtr_1 - int_mtr_2  " << int_mtr_2._value << endl;
    bgnbr_mtr_3 = bgnbr_mtr_1 + bgnbr_mtr_2;
    int_klmtr.as< KiloMeter>() = int_mtr_1.as< Meter>()/1000;
    return 0;
}
