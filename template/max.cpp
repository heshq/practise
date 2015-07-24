#include <iostream>

template< typename T>
T& declval()
{
    return *static_cast< T*>( nullptr);
};

template< typename ...T> struct common_type;

template< typename T>
struct common_type< T>
{
    typedef T value_type;
};

template< typename T1, typename T2>
struct common_type< T1, T2>
{
    typedef decltype( true ?  declval< T1>() : declval< T2>()) value_type;
};

template< typename T1, typename T2, typename... V>
struct common_type< T1, T2, V...>
{
    typedef typename common_type< typename common_type< T1, T2>::value_type, V...>::value_type value_type;
};

template< typename T>
T max( T t)
{
	return t;
};

template< typename N, typename... V>
typename common_type< N, typename common_type< V...>::value_type >::value_type max( N n, V... v)
{
    auto rest_max = max( v...);
    return n > rest_max ? n : rest_max;
};

int main()
{
    auto rst = max( 1, 2, 6, 9.0f, 2u, 3ul);
    std::cout << rst << std::endl;
    return 0;
}
