#ifndef _FIND_MOST_IMPL_H
#define _FIND_MOST_IMPL_H

namespace util
{

    template< typename ITER >
    ITER find_largest( ITER begin, ITER end)
    {
        using namespace std;
        return find_largest( begin, end,
                less< typename iterator_traits< ITER >::value_type >());
    }

    template< typename ITER, typename COMP >
    ITER find_largest( ITER begin, ITER end, COMP less)
    {
        if ( begin == end)
            return end;
        ITER largest = begin;
        while ( ++ begin != end)
            if ( less( *largest, *begin))
                largest = begin;
        return largest;
    }

    template< typename ITER>
    ITER find_smallest( ITER begin, ITER end)
    {
        using namespace std;
        return find_smallest( begin, end,
                less< typename iterator_traits< ITER >::value_type >());
    }

    template< typename ITER, typename COMP >
    ITER find_smallest( ITER begin, ITER end, COMP less)
    {
        if ( begin == end)
            return end;
        ITER smallest = begin;
        while ( ++ begin != end)
            if ( less( *begin, *smallest))
                smallest = begin;
        return smallest;
    }

} // namespace find_most

#endif

