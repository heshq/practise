#ifndef PRIMER_NUMBER_H
#define PRIMER_NUMBER_H


namespace prime_util
{
    namespace prime_util_inner
    {
        template< unsigned target, unsigned current>
        struct Choose {
            static unsigned const value = ( current*current > target) ? 1 : ( ( current + 1 )* ( current + 1) <= target ? 2 : 0 );
        };

        template< unsigned target, unsigned current, unsigned choose = 0>
        struct FindSquareRoot {
            static unsigned const value = current;
        };

        template< unsigned target, unsigned current>
        struct FindSquareRoot< target, current, 1> {
            static unsigned const next = current - ( current*current - target)/( 2*current) - 1;
            static unsigned const value = FindSquareRoot< target, next, Choose< target, next>::value >::value;
        };

        template< unsigned target, unsigned current>
        struct FindSquareRoot< target, current, 2> {
            static unsigned const next = current + ( target - ( current + 1)*( current + 1))/( 2*( current + 1)) + 1;
            static unsigned const value = FindSquareRoot< target, next, Choose< target, next>::value >::value;
        };

        template< unsigned N>
        struct Sqrt {
            static unsigned const value = FindSquareRoot< N, Sqrt< N - 1>:: value, Choose< N, Sqrt< N - 1>:: value>::value>::value;
        };

        template<>
        struct Sqrt< 1> {
            static unsigned const value = 1;
        };

        template< unsigned N, unsigned TestNumber >
        struct PrimeTest {
            static bool const value = N % TestNumber != 0 && PrimeTest< N, TestNumber -1 >::value;
        };

        template< unsigned N>
        struct PrimeTest< N, 2> {
            static bool const value = N == 2 || N % 2 != 0;
        };

        //when N is 3, and the square root is 1
        template< unsigned N>
        struct PrimeTest< N, 1> {
            static bool const value = true;
        };

    }//end of namespace prime_util_inner

    template< unsigned N>
    struct PrimeNumbers {
        PrimeNumbers< N - 1> prifix;
        typedef prime_util_inner::Square< N> Sqrt;
        typedef prime_util_inner::PrimeTest< N ,Sqrt::value> prime_test;
        bool const is_prime_number = prime_test::value;
    };
    
    template<>
    struct PrimeNumbers< 0> {
        bool const is_prime_number = false;
    };

    template<>
    struct PrimeNumbers< 1> {
        PrimeNumber< 0> prifix;
        bool const is_prime_number = false;
    };

    template<>
    struct PrimeNumbers< 2> {
        PrimeNumber< 1> prifix;
        bool const is_prime_number = true;
    };

}// end of namespace prime_util

#endif