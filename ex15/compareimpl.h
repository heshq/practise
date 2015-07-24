#ifndef COMPARE_IMPLEMENT_H
#define COMPARE_IMPLEMENT_H

namespace algorithm_custom
{
    namespace algorithm_custom_inner
    {
    //-----------------traits definition--------------------------
        enum type{
            INT      = 0,
            UNSIGNED = 1,
            FLOAT    = 3
        };

        template< typename T>
        struct arg_traits
        {
            static int const type = INT;
        };
    
#if UCHAR_MAX == CHAR_MAX

        template<>
        struct arg_traits< char>
        {
            static int const type = UNSIGNED;
        };

#endif
    
        template<>
        struct arg_traits< unsigned char>
        {
            static int const type = UNSIGNED;
        };

        template<>
        struct arg_traits< unsigned short>
        {
            static int const type = UNSIGNED;
        };

        template<>
        struct arg_traits< unsigned>
        {
            static int const type = UNSIGNED;
        };

        template<>
        struct arg_traits< unsigned long>
        {
            static int const type = UNSIGNED;
        };

        template<>
        struct arg_traits< float>
        {
            static int const type = FLOAT;
        };

        template<>
        struct arg_traits< double>
        {
            static int const type = FLOAT;
        };

        template<>
        struct arg_traits< long double>
        {
            static int const type = FLOAT;
        };

        //-----------------less definition----------------------------

        //primary template
        template< typename T1, typename T2, int first_arg_type, int second_arg_type>
        struct safe_compare{
            static bool less( T1 x, T2 y)
            {
                return x < y;
            }
        };
        
        //specialization for first arg unsigned
        template< typename T1, typename T2, int second_arg_type>
        struct safe_compare< T1, T2, UNSIGNED, second_arg_type>{
            static bool less( T1 x, T2 y)
            {
                if( y < 0)
                    return false;
                return x < y;
            }
        };
        
        //specialization for second arg unsigned
        template< typename T1, typename T2, int first_arg_type>
        struct safe_compare< T1, T2, first_arg_type, UNSIGNED>{
            static bool less( T1 x, T2 y)
            {
                if( x < 0)
                    return true;
                return x < y;
            }
        };
        
        template< typename T1, typename T2>
        struct safe_compare< T1, T2, FLOAT, FLOAT>
        {
            static bool less( T1 x, T2 y)
            {
                return ( T2)x < ( T1)y;
            }
        };
    }//namespace algorithm_custom_inner end 
    
    template< typename T1, typename T2>
    bool less( T1 x, T2 y)
    {
        using namespace algorithm_custom_inner;
        return safe_compare< T1, T2, arg_traits< T1>::type, arg_traits< T2>::type>::less( x, y);
    }
    
    //-----------------other definition---------------------------

    template< typename T1, typename T2>
    bool less_equal( T1 x, T2 y)
    {
        using namespace algorithm_custom_inner;
        return !safe_compare< T2, T1, arg_traits< T2>::type, arg_traits< T1>::type>::less( y, x);
    }

    template< typename T1, typename T2>
    bool greater( T1 x, T2 y)
    {
        using namespace algorithm_custom_inner;
        return safe_compare< T2, T1, arg_traits< T2>::type, arg_traits< T1>::type>::less( y, x);
    }

    template< typename T1, typename T2>
    bool greater_equal( T1 x, T2 y)
    {
        using namespace algorithm_custom_inner;
        return !safe_compare< T1, T2, arg_traits< T1>::type, arg_traits< T2>::type>::less( x, y);
    }

    template< typename T1, typename T2>
    bool equal( T1 x, T2 y)
    {
        using namespace algorithm_custom_inner;
        return !safe_compare< T1, T2, arg_traits< T1>::type, arg_traits< T2>::type>::less( x, y) 
            && !safe_compare< T2, T1, arg_traits< T2>::type, arg_traits< T1>::type>::less( y, x);
    }
    
}//namespace algorithm_custom end

#endif
