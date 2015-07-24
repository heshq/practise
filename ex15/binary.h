
#ifndef BINARY_H
#define BINARY_H

template< unsigned T>
struct Binary
{
    static unsigned const value = T % 10 + Binary< T / 10>::value * 2;
    static_assert( T % 10 < 2 , "illegality binary code");
};

template<>
struct Binary< 0>
{
    static unsigned const value = 0u;
};

//unnecessary specialization
//template<>
//struct Binary< 1>
//{
//    static unsigned const value = 1u;
//};

#endif
