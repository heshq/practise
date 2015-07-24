#ifndef _SAFE_COMPARE_H
#define _SAFE_COMPARE_H

#include <climits>      // CHAR_MIN

namespace util
{

    template< typename T1, typename T2 > bool less( T1 const &, T2 const &);
    template< typename T1, typename T2 > bool less_equal( T1 const &, T2 const &);
    template< typename T1, typename T2 > bool greater( T1 const &, T2 const &);
    template< typename T1, typename T2 > bool greater_equal( T1 const &, T2 const &);
    template< typename T1, typename T2 > bool equal( T1 const &, T2 const &);
    template< typename T1, typename T2 > bool not_equal( T1 const &, T2 const &);

}

#include "safe_compare_impl.h"

#endif

