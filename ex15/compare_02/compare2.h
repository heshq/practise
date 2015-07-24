#ifndef COMPARE_H
#define COMPARE_H
#include <climits>

namespace custom_compare
{

    //---------------------definition less begin---------------------------
    template< typename T, typename U>
    struct less
    {
        bool operator()( T a, U b);
    };

    template< typename T, typename U>
    bool less< T, U>::operator()( T a, U b)
    {
        return a < b;
    }

    template<> bool less< float, double>::operator()( float a, double b);
    template<> bool less< double, float>::operator()( double a, float b);
    template<> bool less< float, long double>::operator()( float a, long double b);
    template<> bool less< long double, float>::operator()( long double a, float b);
    template<> bool less< double, long double>::operator()( double a, long double b);
    template<> bool less< long double, double>::operator()( long double a, double b);
    
#if CHAR_MAX == UCHAR_MAX
    template< typename T>
    struct less< T, char>
    {
        bool operator()( T a, unsigned long b);
    };

    template< typename T>
    bool
    less< T, char>::operator()( T a, char b)
    {
        if( a < 0)
            return true;
        return a < b;
    }

    template< typename T>
    struct less< char, T>
    {
        bool operator()( char a, T b);
    };

    template< typename T>
    bool
    less< char, T>::operator()( char a, T b)
    {
        if( b < 0)
            return false;
        return a < b;
    }
#endif

    template< typename T>
    struct less< T, unsigned long>
    {
        bool operator()( T a, unsigned long b);
    };

    template< typename T>
    bool
    less< T, unsigned long>::operator()( T a, unsigned long b)
    {
        if( a < 0)
            return true;
        return a < b;
    }

    template< typename T>
    struct less< T, unsigned>
    {
        bool operator()( T a, unsigned b);
    };

    template< typename T>
    bool
    less< T, unsigned>::operator()( T a, unsigned b)
    {
        if( a < 0)
            return true;
        return a < b;
    }

    template< typename T>
    struct less< T, unsigned short>
    {
        bool operator()( T a, unsigned short b);
    };

    template< typename T>
    bool
    less< T, unsigned short>::operator()( T a, unsigned short b)
    {
        if( a < 0)
            return true;
        return a < b;
    }

    template< typename T>
    struct less< T, unsigned char>
    {
        bool operator()( T a, unsigned char b);
    };

    template< typename T>
    bool
    less< T, unsigned char>::operator()( T a, unsigned char b)
    {
        if( a < 0)
            return true;
        return a < b;
    }


    template< typename T>
    struct less< unsigned long, T>
    {
        bool operator()( unsigned long a, T b);
    };

    template< typename T>
    bool
    less< unsigned long, T>::operator()( unsigned long a, T b)
    {
        if( b < 0)
            return false;
        return a < b;
    }

    template< typename T>
    struct less< unsigned, T>
    {
        bool operator()( unsigned a, T b);
    };

    template< typename T>
    bool
    less< unsigned, T>::operator()( unsigned a, T b)
    {
        if( b < 0)
            return false;
        return a < b;
    }

    template< typename T>
    struct less< unsigned short, T>
    {
        bool operator()( unsigned short a, T b);
    };

    template< typename T>
    bool
    less< unsigned short, T>::operator()( unsigned short a, T b)
    {
        if( b < 0)
            return false;
        return a < b;
    }

    template< typename T>
    struct less< unsigned char, T>
    {
        bool operator()( unsigned char a, T b);
    };

    template< typename T>
    bool
    less< unsigned char, T>::operator()( unsigned char a, T b)
    {
        if( b < 0)
            return false;
        return a < b;
    }
    //---------------------definition less over----------------------------

    //---------------------definition less_equal begin---------------------
    template< typename T, typename U>
    struct less_equal
    {
        bool operator()( T a, U b);
    };

    template< typename T, typename U>
    bool less_equal< T, U>::operator()( T a, U b)
    {
        less< U, T> compare;
        return !compare( b, a);
    }
    //---------------------definition less_equal over----------------------

    //---------------------definition greater begin------------------------
    template< typename T, typename U>
    struct greater
    {
        bool operator()( T a, U b);
    };

    template< typename T, typename U>
    bool greater< T, U>::operator()( T a, U b)
    {
        less< U, T> compare;
        return compare( b, a);
    }
    //---------------------definition greater over-------------------------

    //---------------------definition greater_equal begin------------------
    template< typename T, typename U>
    struct greater_equal
    {
        bool operator()( T a, U b);
    };

    template< typename T, typename U>
    bool greater_equal< T, U>::operator()( T a, U b)
    {
        less< T, U> compare;
        return !compare( a, b);
    }
    //---------------------definition greater_equal over-------------------

    //---------------------definition equal begin--------------------------
    template< typename T, typename U>
    struct equal
    {
        bool operator()( T a, U b);
    };

    template< typename T, typename U>
    bool equal< T, U>::operator()( T a, U b)
    {
        less< T, U> compare1;
        less< U, T> compare2;
        return !compare1( a, b) && !compare2( b, a);
    }
    //---------------------definition equal over---------------------------

}// namespace custom_compare end

#endif
