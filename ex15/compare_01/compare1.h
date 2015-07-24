#ifndef COMPARE_H
#define COMPARE_H

#include <cfloat> // FLT_MIN,DBL_EPSILON
#include <climits>// CHAR_MAX

template< typename T, typename U>
struct isSameType
{
    static bool const value = false;
};

template< typename T>
struct isSameType< T, T>
{
    static bool const value = true;
};

template< typename T>
bool isUnsigned( T a){
    return isSameType< T, unsigned char>::value 
#if CHAR_MAX != 127 //unsigned char
        || isSameType< T, char>::value
#endif
        || isSameType< T, unsigned short>::value
        || isSameType< T, unsigned>::value
        || isSameType< T, unsigned long>::value;
}

template< typename T>
bool isFloatNumber( T a){
    return isSameType< T, float>::value 
        || isSameType< T, double>::value
        || isSameType< T, long double>::value;
}

template< typename T, typename U>
bool compare( T a, U b)
{
    if( isSameType< T, U>::value)
        return a < b;
    if( isUnsigned< T>( a)){
        if( b < 0)
            return false;
        return a < b;
    }
    if( isUnsigned< U>( a)){
        if( a < 0 )
            return true;
        return a < b;
    }
    if( isSameType< T ,float>::value && isFloatNumber< U>( b)){
    	return a < b - FLT_EPSILON / 2;//error here
    }
    if( isSameType< U ,float>::value && isFloatNumber< T>( a)){
    	return a + FLT_EPSILON < b;//error here
    }
    if( isSameType< T ,double>::value && isFloatNumber< U>( b)){
    	return a < b - DBL_EPSILON / 2;//error here
    }
    if( isSameType< U ,double>::value && isFloatNumber< T>( a)){
    	return a + DBL_EPSILON / 2 < b;//error here
    }
    return a < b;
}


//template< typename T>
//bool compare( T a, unsigned short b)
//{
//    if( a < 0)
//        return true;
//    return a < b;
//}

//template< typename T>
//bool compare( T a, unsigned b)
//{
//    if( a < 0)
//        return true;
//    return a < b;
//}

//template< typename T>
//bool compare( T a, unsigned long b)
//{
//    if( a < 0)
//        return true;
//    return a < b;
//}

//template< typename T>
//bool compare( unsigned short a, T b)
//{
//    if( b < 0)
//        return false;
//    return a < b;
//}
//
//template< typename T>
//bool compare( unsigned a, T b)
//{
//    if( b < 0)
//        return false;
//    return a < b;
//}

//template< typename T>
//bool compare( unsigned long a, T b)
//{
//    if( b < 0)
//        return false;
//    return a < b;
//}

//bool compare( float a, double b);
//bool compare( double a, float b);
//bool compare( float a, long double b);
//bool compare( long double a, float b);
//bool compare( double a, long double b);
//bool compare( long double a, double b);


#endif
