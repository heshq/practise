#include <iostream>
#include <ios>

template< typename T>
struct type_wapper{
    typedef T value_type;
    typedef T& refrence_type;
    typedef T* point_type;
};


template< typename T>
struct type_wapper< T&>{
    typedef T value_type;
    typedef T& refrence_type;
    typedef T* point_type;
};

template< typename T>
struct type_wapper< T*>{
    typedef T value_type;
    typedef T& refrence_type;
    typedef T* point_type;
};

template< typename T, unsigned LINE, unsigned COLUMN>
struct matrix
{
    matrix( int a){}
};

template< typename T>
T& declval()
{
    return *static_cast< T*>( nullptr);
};

template< typename T1, typename T2>
struct common_type
{
    //typedef decltype( true ?  T1() : T2()) value_type;//error if no default construct
    typedef decltype( true ?  declval< T1>() : declval< T2>()) value_type;
};

template< typename T>
struct common_type
{
    typedef T value_type;
};

template< typename T1, typename T2, typename... V>
struct common_type
{
    typedef typename common_type < typename common_type< T1, T2>::value_type, V...> value_type;
};


int main()
{
    type_wapper< int *>::point_type it ;
    int i1 = 2;
    it = &i1;
    //unsigned short us = unsigned short( b);//error,expect (
    //unsigned short us = ( unsigned short) b;//correct
    //unsigned short us = type_wapper< unsigned short>::value_type b;//expect ( for type cast
    unsigned short us = type_wapper< unsigned short>::value_type( i1);
    type_wapper< int>::refrence_type ir = i1;
    type_wapper< int>::point_type it2 = &i1;
    std::cout << *it << " " << i1 << " " << ir << " "<< *it2 << std::endl;
    i1 = 4;
    std::cout << *it << " " << i1 << " " << ir << " "<< *it2 << std::endl;

    decltype( true? 1: 1.0f) f;
    f = 123.456;
    std::cout << std::fixed << std::endl;
    std::cout <<  f << std::endl;
    return 0;
}
