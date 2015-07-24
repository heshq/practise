#ifndef METERING_SYSTEM_H
#define METERING_SYSTEM_H
#include <type_traits>// for std::common_type

namespace metering_system
{
    namespace metering_system_inner
    {
    	struct BritishSystem{};
        struct InternationalSystem{};
        //for foundation type
        struct NoneSystemTag{};
    }

    typedef metering_system_inner::BritishSystem BS;
    typedef metering_system_inner::InternationalSystem IS;

    struct MS{
        static BS const bs;  
        static IS const is; 
    };

    class Setter;
    // T1 can only be BritishSystem or InternationalSystem
    template< typename T1, typename T2> class Metering;
}

//template< typename T1, typename T2, typename T3>
//metering_system::Metering< T1,
//    typename std::common_type< T2, typename metering_system::metering_system_inner::MS_traits< T3>::value_type >::type > 
//operator+( metering_system::Metering< T1, T2> a,T3 b);

namespace metering_system
{
    template< typename T1, typename T2>
    class Metering{
        
        public:
            friend class Setter;

            //template<typename T3>
            //friend Metering< T1, typename std::common_type< T2, typename metering_system_inner::MS_traits< T3>::value_type >::type > 
            //operator+( Metering< T1, T2> a,T3 b);

            //operator +
            template< typename T3> Metering< T1, typename std::common_type< T2, T3 >::type >
            operator+( T3 other);
            template< typename T3, typename T4> Metering< T1, typename std::common_type< T2, T4 >::type > 
            operator+( Metering< T3, T4> other);
            //operator -
            template< typename T3>
            Metering< T1, typename std::common_type< T2, T3 >::type > 
            operator-( T3 other);
            template< typename T3, typename T4>
            Metering< T1, typename std::common_type< T2, T4 >::type > 
            operator-( Metering< T3, T4> other);
            //operator <
            template< typename T3> bool operator<( T3 other);
            template< typename T3, typename T4> bool operator<( Metering< T3, T4> other);
            //operator <=
            template< typename T3> bool operator<=( T3 other);
            template< typename T3, typename T4> bool operator<=( Metering< T3, T4> other);
            //operator >
            template< typename T3> bool operator>( T3 other);
            template< typename T3, typename T4> bool operator>( Metering< T3, T4> other);
            //operator >=
            template< typename T3> bool operator>=( T3 other);
            template< typename T3, typename T4> bool operator>=( Metering< T3, T4> other);
            //operator ==
            template< typename T3> bool operator==( T3 other);
            template< typename T3, typename T4> bool operator==( Metering< T3, T4> other);
            //operator !=
            template< typename T3> bool operator!=( T3 other);
            template< typename T3, typename T4> bool operator!=( Metering< T3, T4> other);
            
            typedef T1 metering_type;
            typedef T2 value_type;

            value_type _value;

            Metering( T2 value):_value( value){}
            Metering( const Metering &other):_value( other._value){}

            class Setter{
       
                private:
                    Metering &_owner;

                public:
                    Setter( Metering &metering): _owner( metering){}
                    Setter( const Setter &other): _owner( other._owner){}
                    operator T2() const { return _owner._value; }
    
            };//class Setter over
    
            //param only allowed bs or is
            template< typename MeteringType> Setter operator()( MeteringType ms);
            Metering& operator=( const Metering &other);
    };// class Metering over
}//namespace metering_system over

#include "metering_system_impl.h"

#endif
