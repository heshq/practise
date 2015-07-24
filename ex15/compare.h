#ifndef COMPARE_H
#define COMPARE_H
#include <climits> //UCHAR_MAX, CHAR_MAX

namespace algorithm_custom
{
    template< typename T1, typename T2> bool less( T1 x, T2 y);
    template< typename T1, typename T2> bool less_equal( T1 x, T2 y);
    template< typename T1, typename T2> bool greater( T1 x, T2 y);
    template< typename T1, typename T2> bool greater_equal( T1 x, T2 y);
    template< typename T1, typename T2> bool equal( T1 x, T2 y);
    
}// namespace algorithm_custom end

#include "compareimpl.h"

#endif