#ifndef _FIND_MOST_H
#define _FIND_MOST_H

#include <iterator>     // std::iterator_traits
#include <algorithm>    // std::less

namespace util
{

    template< typename ITER>
    ITER find_largest( ITER begin, ITER end);

    template< typename ITER, typename COMP >
    ITER find_largest( ITER begin, ITER end, COMP);

    template< typename ITER>
    ITER find_smallest( ITER begin, ITER end);

    template< typename ITER, typename COMP>
    ITER find_smallest( ITER begin, ITER end, COMP);

}

#include "find_most_impl.h"

#endif

