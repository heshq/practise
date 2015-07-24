#ifndef MIN_MAX_H
#define MIN_MAX_H
#include <functional>
#include <iterator>

namespace algorithm_custom
{

    //compare should return the smaller element 
    template< typename T, typename compare = std::less< typename std::iterator_traits< T>::value_type > >
    T min_element( T first, T end, compare less = std::less< typename std::iterator_traits< T>::value_type >() )
    {
        if( first == end)
            return end;
        T min = first;
        while( ++first != end)
            if( less( *first , *min ))
                min = first;
        return min;
    }

    //compare should return the smaller element 
    template< typename T, typename compare = std::less< typename std::iterator_traits< T>::value_type > >
    T max_element( T first, T end, compare less = std::less< typename std::iterator_traits< T>::value_type >() )
    {
        if( first == end)
            return end;
        T max = first;
        while( ++first != end)
            if( less( *max , *first ))
                max = first;
        return max;
    }

}//namespace algorithm_custom end 

#endif
