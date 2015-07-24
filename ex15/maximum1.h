#ifndef MAXIMUM_H
#define MAXIMUM_H

//need use traits,so this version is not so usefull

//find maximum T::value_type when T is a iterator
template< typename T, typename compare = std::less< T> >
typename T::value_type maximum( T begin, T end)
{
    typename T::value_type max = * begin;
    while( begin++ != end){
        if( compare( max, *begin ))
            max = *begin;
    }
    return max;
}

//find maximum T in a array
template< typename T, typename compare = std::less< T> >
T maximum( T * begin, T * end)
{
    T max = *begin;
    while( begin++ != end)
        if( compare( max, *begin ))
            max = * begin;
    return max;
}

#endif
