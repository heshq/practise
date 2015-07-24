#ifndef PRIME_NUMBER_H
#define PRIME_NUMBER_H

namespace prime_util
{
    template< unsigned target, unsigned N>
    struct SquareRootTest{
        static bool const value = N*N <= target && ( N + 1)*( N + 1) > target;  
    };

    template< unsigned y, unsigned x, bool choose = true>
    struct NextCurrent{
        static unsigned const value = x - ( x*x - y)/( 2*x) - 1;
    };

    template< unsigned y, unsigned x>
    struct NextCurrent< y, x, false>{
        static unsigned const value = x + ( y - ( x + 1)*( x + 1))/( 2*( x + 1)) + 1;
    };

    template< unsigned target, unsigned current, bool is_right = true>
    struct FindSquareRoot{
        static unsigned const value = current;
    };

    template< unsigned target, unsigned current>
    struct FindSquareRoot< target, current, false>{
    	typedef NextCurrent< target, current, ( current * current > target)> next;
        static unsigned const value = FindSquareRoot< target ,next::value
        ,SquareRootTest< target, next::value >::value >::value;
    };

    template< unsigned target>
    struct Square
    {
    	static unsigned const value = FindSquareRoot< target, 1, SquareRootTest< target, 1>::value >::value;
    };
}

#endif
