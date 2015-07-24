#ifndef _PRIME_TABLE_H
#define _PRIME_TABLE_H

namespace util
{

    template< unsigned N, unsigned M = 0 >
    struct is_prime {
        static bool const value = N % M && is_prime< N, M - 1 >::value;
    };
    
    template< unsigned N >
    struct is_prime< N, 1 > {
        static bool const value = true;
    };
    
    template< unsigned N >
    struct is_prime< N, 0 > {
        static bool const value = is_prime< N, N - 1 >::value;
    };
    
    template<>
    struct is_prime< 1, 0 > {
        static bool const value = false;
    };
    
    template<>
    struct is_prime< 0, 0 > {
        static bool const value = false;
    };
    
    template< unsigned N >
    struct prime_table {
        prime_table< N - 1 > prefix;
        bool const value = is_prime< N >::value;
    };
    
    template<>
    struct prime_table< 0 > {
        bool const value = is_prime< 0 >::value;
    };
} // namespace util

#endif
