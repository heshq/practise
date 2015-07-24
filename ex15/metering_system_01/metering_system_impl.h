#ifndef METERING_SYSTEM_IMPL_H
#define METERING_SYSTEM_IMPL_H

namespace metering_system
{

    template< typename T1, typename T2>
    template< typename MeteringType>
    typename Metering< T1, T2>::Setter
    Metering< T1, T2>::operator()( MeteringType ms)
    {
        static_assert(  std::is_same< metering_type, MeteringType>::value
            ,"metering system incorrect");
        return Setter( *this);
    }
    
    template< typename T1, typename T2>
    Metering< T1, T2>&
    Metering< T1, T2>::operator=( const Metering &other)
    {
        static_assert(  std::is_same< typename Metering< T1, T2>::metering_type,  typename Metering::metering_type >::value 
            ,"can not assign value to a difference metering system");
        _value = other._value;
        return *this;
    }

    template< typename T1, typename T2>
    template< typename T3>
    Metering< T1, typename std::common_type< T2, T3 >::type > 
    Metering< T1, T2>::operator+( T3 other)
    {
        typedef typename std::common_type< T2, T3>::type result_value_type;
        typedef Metering< T1 , result_value_type> result_type;

        auto rst = _value + other;
        result_type result( rst);
        return result;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    Metering< T1, typename std::common_type< T2, T4 >::type > 
    Metering< T1, T2>::operator+( Metering< T3, T4> other)
    {
        typedef typename std::common_type< T2, T4 >::type result_value_type;
        typedef Metering< T1 , result_value_type> result_type;

        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        auto rst = _value + other._value;
        result_type result( rst);
        return result;
    }

    template< typename T1, typename T2>
    template< typename T3>
    Metering< T1, typename std::common_type< T2, T3 >::type > 
    Metering< T1, T2>::operator-( T3 other)
    {
        typedef typename std::common_type< T2, T3 >::type result_value_type;
        typedef Metering< T1 , result_value_type> result_type;

        auto rst = _value - other;
        result_type result( rst);
        return result;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    Metering< T1, typename std::common_type< T2, T4 >::type > 
    Metering< T1, T2>::operator-( Metering< T3, T4> other)
    {
        typedef typename std::common_type< T2, T4 >::type result_value_type;
        typedef Metering< T1 , result_value_type> result_type;

        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        auto rst = _value - other._value;
        result_type result( rst);
        return result;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator<( T3 other)
    {
        return _value < other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator<( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value < other._value;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator<=( T3 other)
    {
        return _value <= other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator<=( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value <= other._value;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator>( T3 other)
    {
        return _value > other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator>( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value > other._value;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator>=( T3 other)
    {
        return _value >= other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator>=( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value >= other._value;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator==( T3 other)
    {
        return _value == other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator==( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value == other._value;
    }

    template< typename T1, typename T2>
    template< typename T3>
    bool
    Metering< T1, T2>::operator!=( T3 other)
    {
        return _value != other;
    }

    template< typename T1, typename T2>
    template<typename T3, typename T4>
    bool
    Metering< T1, T2>::operator!=( Metering< T3, T4> other)
    {
        static_assert( std::is_same< T1, T3>::value, "can not calculate with difference metering system" );
        return _value != other._value;
    }
}//namespace metering_system over


//template< typename T1, typename T2, typename T3>
//metering_system::Metering< T1 
//    ,typename std::common_type< T2, typename metering_system::metering_system_inner::MS_traits< T3>::value_type >::type > 
//operator+( metering_system::Metering< T1, T2> a,T3 b)
//{
//    typedef typename metering_system::Metering< T1, T2> param_a_type;
//    typedef metering_system::metering_system_inner::MS_traits< T3> param_b_traits;
//    typedef metering_system::metering_system_inner::NoneSystemTag none;
//    typedef typename std::common_type< T2, typename param_b_traits::value_type >::type result_value_type;
//    typedef metering_system::Metering< T1 ,  result_value_type> result_type;

//    static_assert( std::is_same< none, typename param_b_traits::metering_type>::value
//        || std::is_same< typename param_a_type::metering_type, typename param_b_traits::metering_type>::value  
//        , "can not calculate with difference metering system");
//    auto rst = a._value + ( typename param_b_traits::value_type)b;
//    result_type result( rst);
//    return result;
//}

#endif
