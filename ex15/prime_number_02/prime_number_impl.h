#ifndef PRIME_NUMBER_IMPL_H
#define PRIME_NUMBER_IMPL_H

namespace prime_number_util
{

    namespace prime_number_util_inner
    {

        template< unsigned N1, unsigned N2>
        struct IsPrimeNumber{
            static bool const value =  N1%N2 != 0 && IsPrimeNumber< N1, N2-1 >::value;
        };
    
        template< unsigned N>
        struct IsPrimeNumber< N, 2>{
            static bool const value = ( N == 2 ) ? true : N%2 != 0;
        };

    }//namespace prime_number_util_inner end

    template< unsigned N>
    struct Number{
        Number< N - 1> prifix;
        typedef prime_number_util_inner::IsPrimeNumber< N, N-1 > IsPrimeNumber;
        bool const is_prime_number = IsPrimeNumber::value;
    };
    
    template<>
    struct Number< 0u>{ 
        bool const is_prime_number = false;
    };

    template<>
    struct Number< 1u>{
        Number< 0u> prifix;
        bool const is_prime_number = false;
    };

    template<>
    struct Number< 2u>{
        Number< 1u> prifix;
        bool const is_prime_number = true;
    };

}//namespace prime_number_util end
#endif
