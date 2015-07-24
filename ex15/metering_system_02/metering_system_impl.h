#ifndef METERING_SYSTEM_IMPL_H
#define METERING_SYSTEM_IMPL_H

namespace metering_system
{
    template< typename T1, typename T2> class Metering;
    namespace metering_system_inner
    {
        template< typename T>
        struct MS_traits{
            typedef T value_type;
            typedef NoMeteringSystem metering_type;
        };
    }//end of namespace metering_system_inner
    
    class Setter;

    template< typename T1, typename T2>
    class Metering{
        
        public:
            friend class Setter;
            
            typedef T1 metering_type;
            typedef T2 value_type;
            
        private:
            value_type _value;
            operator T2() { return _value; }
            
        public:
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
            template< typename MeteringType> Setter operator()() {
                static_assert(  std::is_same< metering_type, MeteringType>::value
                        ,"metering system incorrect");
                return Setter( *this);
            }
            
            template< typename MeteringType>
            Metering& operator=( const MeteringType &other) {
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< MeteringType>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< MeteringType>::metering_type>::value 
                        ,"can not assign value to a difference metering system");
                _value = ( typename MS_traits< MeteringType>::value_type)other;
                return *this;
            }
            
            template< typename T3>
            friend Metering< T1, typename std::common_type< T2, typename metering_system_inner::MS_traits< T3>::value_type >::type > 
            operator+( T3 other)
            {
                using namespace metering_system_inner;
                typedef typename std::common_type< T2, typename MS_traits< T3>::value_type >::type result_value_type;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                auto rst = a._value + ( typename MS_traits< T3>::value_type)other;
                Metering< T1 ,  result_value_type> result( rst);
                return result;
            }
            
            template< typename T3>
            friend Metering< T1, typename std::common_type< T2, typename metering_system_inner::MS_traits< T3>::value_type >::type > 
            operator-( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                typedef typename std::common_type< T2, typename MS_traits< T3>::value_type >::type result_value_type;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                auto rst = a._value - ( typename MS_traits< T3>::value_type)b;
                Metering< T1 ,  result_value_type> result( rst);
                return result;
            }
            
            template< typename T3>
            friend bool
            operator<( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value < ( typename MS_traits< T3>::value_type)b;
            }
            
            template< typename T3>
            friend bool
            operator<=( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value <= ( typename MS_traits< T3>::value_type)b;
            }
            
            template< typename T3>
            friend bool
            operator>( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value > ( typename MS_traits< T3>::value_type)b;
            }
            
            template< typename T3>
            friend bool
            operator>=( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value >= ( typename MS_traits< T3>::value_type)b;
            }
            
            template< typename T3>
            friend bool
            operator==( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value == ( typename MS_traits< T3>::value_type)b;
            }
            
            template< typename T3>
            friend bool
            operator!=( Metering< T1, T2> a,T3 b)
            {
                using namespace metering_system_inner;
                
                static_assert( std::is_same< NoMeteringSystem, typename MS_traits< T3>::metering_type>::value
                        || std::is_same< metering_type, typename MS_traits< T3>::metering_type>::value 
                        , "can not calculate with difference metering system");
                return a._value != ( typename MS_traits< T3>::value_type)b;
            }
    };// end of class Metering
    
    namespace metering_system_inner
    {
        template<>
        struct MS_traits< Metering>{
            typedef typename Metering::value_type value_type;
            typedef typename Metering::metering_type metering_type;
        };
    }//end of namespace metering_system_inner
}//end of namespace metering_system


#endif
