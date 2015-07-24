#ifndef PRIME_NUMBER_H
#define PRIME_NUMBER_H

namespace prime_util
{
    template< unsigned Target, unsigned N>
    struct SquareRootTest{
        static bool const value = N*N <= Target  &&  ( N + 1)*( N + 1) > Target ;
    };

    template< unsigned Lower, unsigned Upper, bool Choose = true>
    struct Choose
    {
        static unsigned const lower = Lower;
        static unsigned const upper = ( Upper + Lower)/2;
    };

    template< unsigned Lower, unsigned Upper>
    struct Choose< Lower, Upper, false>
    {
        static unsigned const lower = ( Upper + Lower)/2;
        static unsigned const upper = Upper;
    };

    template< unsigned Target , unsigned Lower = 0, unsigned Upper = Target>
    struct FindSquareRoot{
        typedef Choose< Lower, Upper, ( ( Upper + Lower)*( Upper + Lower)/4 > Target )> choose;
        static unsigned const value 
            = SquareRootTest< Target, ( Upper + Lower)/2 >::value
            ? ( Upper + Lower)/2 
            : FindSquareRoot< Target, choose::lower, choose::upper>::value;
    };
}

#endif
