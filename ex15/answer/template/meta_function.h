#ifndef _META_FUNCTION_H
#define _META_FUNCTION_H

namespace util
{
    namespace meta_function
    {
        template< typename T1, typename T2 >
        struct is_same {
            static bool const value = false;
        };
    
        template< typename T >
        struct is_same< T, T > {
            static bool const value = true;
        };
    
        template< int A, int ... OTHER >
        struct max_int {
            static int const value = A > max_int< OTHER... >::value
                                        ? A
                                        : max_int< OTHER... >::value;
        };
        
        template< int A >
        struct max_int< A > {
            static int const value = A;
        };
        
    } // namespace meta_function
} // namespace util

#endif
