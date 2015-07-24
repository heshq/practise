#ifndef PRIMER_NUMBER_H
#define PRIMER_NUMBER_H


namespace prime_util
{
    namespace prime_util_inner
    {
        template< unsigned y, unsigned x>
        struct Choose{
            static unsigned const value = ( x*x > y) ? 1 : ( ( x + 1 )* ( x + 1) <= y ? 2 : 0 );
        };

        template< unsigned y, unsigned x, unsigned choose = 0>
        struct FindSquareRoot{
            static unsigned const value = x;
        };

        template< unsigned y, unsigned x>
        struct FindSquareRoot< y, x, 1>{
            static unsigned const next = x - ( x*x - y)/( 2*x) - 1;
            static unsigned const value = FindSquareRoot< y, next, Choose< y, next>::value >::value;
        };

        template< unsigned y, unsigned x>
        struct FindSquareRoot< y, x, 2>{
            static unsigned const next = x + ( y - ( x + 1)*( x + 1))/( 2*( x + 1)) + 1;
            static unsigned const value = FindSquareRoot< y, next, Choose< y, next>::value >::value;
        };

        template< unsigned N>
        struct Square
        {
            static unsigned const value = FindSquareRoot< N, Square< N - 1>:: value, Choose< N, Square< N - 1>:: value>::value>::value;
        };

        template<>
        struct Square< 1>
        {
            static unsigned const value = 1;
        };

        template< unsigned N, unsigned TestNumber >
        struct PrimeTest
        {
            static bool const value = N % TestNumber != 0 && PrimeTest< N, TestNumber -1 >::value;
        };

        template< unsigned N>
        struct PrimeTest< N, 2>
        {
            static bool const value = N % 2 != 0;
        };

        template< unsigned N>
        struct PrimeTest< N, 1>
        {
            static bool const value = true;
        };

    }//end of namespace prime_util_inner

    template< unsigned N> struct PrimeNumber;

    template<>
    struct PrimeNumber< 0>{
        bool const is_prime_number = false;
    };

    template<>
    struct PrimeNumber< 1>{
        PrimeNumber< 0> prifix;
        bool const is_prime_number = false;
    };

    template<>
    struct PrimeNumber< 2>{
        PrimeNumber< 1> prifix;
        bool const is_prime_number = true;
    };

    template< unsigned N>
    struct PrimeNumber{
        PrimeNumber< N - 1> prifix;
        typedef prime_util_inner::Square< N> square;
        typedef prime_util_inner::PrimeTest< N ,square::value> prime_test;
        bool const is_prime_number = prime_test::value;
    };
}

#endif