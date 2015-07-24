#ifndef _BINARY_H
#define _BINARY_H

namespace util
{

    template< unsigned long long N >
    struct binary {
        static_assert( N % 10 <= 1, "binary<>: digits in binary numbers can only be 1 or 0");
        static const unsigned long long value = ( N % 10 ? 1 : 0) + 2 * binary< N / 10 >::value;
    };

    template<>
    struct binary< 0 > {
        static const unsigned long long value = 0;
    };

}

#endif

