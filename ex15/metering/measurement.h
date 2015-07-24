#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <type_traits>

namespace measurement
{
    struct Mil{};
    struct Line{};
    struct Inch{};
    struct Foot{};
    struct Yard{};
    struct KiloMeter{};
    struct Meter{};
    struct DeciMetre{};
    struct CentiMeter{};
    struct MilliMeter{};
    struct Micro{};

    template< typename MeasuringUnit, typename ValueType>
    class Number{
        public:
            ValueType _value;

            explicit Number( ValueType value) : _value( value){}

            template< typename ValueType_1>
            ValueType& as()
            { 
                static_assert( std::is_same< MeasuringUnit, ValueType_1>::value, "incorrect measuring unit");
                return _value;
            }
            
            template< typename ValueType_1>
            ValueType const as() const
            { 
                static_assert( std::is_same< MeasuringUnit, ValueType_1>::value, "error : incorrect measuring unit");
                return _value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            Number< MeasuringUnit, ValueType> operator= ( Number< MeasuringUnit_1, ValueType_1> const other) 
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : assigned with difference measuring unit");
                static_assert( std::is_same< ValueType, ValueType_1>::value, "error : assigned with difference value type");
                _value = other._value; 
                return *this;
            }
            
            template< typename MeasuringUnit_1,typename ValueType_1>
            Number< MeasuringUnit, ValueType >& operator+= ( Number< MeasuringUnit_1, ValueType_1> const other)
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : calculate with difference measuring unit");
                static_assert( std::is_same< ValueType, ValueType_1>::value, "error : assigned with difference value type");
                _value += other._value;
                return *this;
            }
            
            template< typename MeasuringUnit_1,typename ValueType_1>
            Number< MeasuringUnit, ValueType >& operator-= ( Number< MeasuringUnit_1, ValueType_1> const other)
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : calculate with difference measuring unit");
                static_assert( std::is_same< ValueType, ValueType_1>::value, "error : assigned with difference value type");
                _value -= other._value;
                return *this;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            Number< MeasuringUnit, typename std::common_type< ValueType, ValueType_1>::type > operator+ ( Number< MeasuringUnit_1, ValueType_1> const other) 
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : calculate with difference measuring unit");
                Number< MeasuringUnit, typename std::common_type< ValueType, ValueType_1>::type> result( _value + other._value);
                return result;
            }
            
            template< typename MeasuringUnit_1,typename ValueType_1>
            Number< MeasuringUnit, typename std::common_type< ValueType, ValueType_1>::type > operator- ( Number< MeasuringUnit_1, ValueType_1> const other)
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : calculate with difference measuring unit");
                Number< MeasuringUnit, typename std::common_type< ValueType, ValueType_1>::type> result( _value - other._value);
                return result;
            }
            
            Number< MeasuringUnit, ValueType >& operator++()
            {
                ++_value;
                return *this;
            }
            
            Number< MeasuringUnit, ValueType >& operator--()
            {
                --_value;
                return *this;
            }
            
            Number< MeasuringUnit, ValueType > operator++( int)
            {
                Number< MeasuringUnit, ValueType> result( _value);
                _value++;
                return result;
            }
            
            Number< MeasuringUnit, ValueType > operator--( int)
            {
                Number< MeasuringUnit, ValueType> result( _value);
                _value--;
                return result;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator< ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value < other._value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator<= ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value <= other._value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator> ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value > other._value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator>= ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value >= other._value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator== ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value == other._value;
            }

            template< typename MeasuringUnit_1,typename ValueType_1>
            bool operator!= ( Number< MeasuringUnit_1, ValueType_1> const other) const
            {
                static_assert( std::is_same< MeasuringUnit, MeasuringUnit_1>::value, "error : compare with difference measuring unit");
                return _value != other._value;
            }
    };
}

#endif
