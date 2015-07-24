#include <iostream>

template<typename T>
T& declval()
{
    return *static_cast< T*>( nullptr);
}

template< typename... T> struct common_type;

template< typename T1, typename T2>
struct common_type< T1, T2>{
    typedef decltype( true ? declval< T1>(): declval< T2>()) value_type;
};

template< typename T1, typename T2, typename... V>
struct common_type< T1, T2, V...>{
    typedef typename common_type< typename common_type< T1, T2>::value_type, V...>::value_type value_type;
};

template< typename T>
T sum( T t)
{
    return t;
}

template< typename T, typename... V>
typename common_type< T, V...>::value_type sum( T t, V... v){
    return t + sum( v...);
}

int main()
{
    using namespace std;
    auto rst = sum( 1, 3.0, 1u, 10);
    cout << rst << endl;
    return 0;
}
