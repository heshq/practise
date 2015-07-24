#ifndef _UNIT_H
#define _UNIT_H

#include "meta_function.h"

namespace util
{
    template< typename UNIT, typename VALUE >
    struct quantity {
        quantity() {}
        quantity( VALUE v) : value( v) {}
        template< typename VALUE2 >
        quantity( quantity< UNIT, VALUE2 > const &q) : value( q.as< UNIT >()) {}
        
        template< typename UNIT2, typename VALUE2 >
        quantity &operator=( quantity< UNIT2, VALUE2 > const &q)
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                "quantity<>: assignment operation of different unit is not allowed!");
            value = q.as< UNIT >();
            return *this;
        }
        
        template< typename UNIT2, typename VALUE2 >
        quantity< UNIT, decltype( VALUE() + VALUE2()) > operator+( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                "quantity<>: plus operation of different unit is not allowed!");
            return quantity< UNIT, decltype( VALUE() + VALUE2()) >( value + q.as< UNIT >());
        }
        
        template< typename UNIT2, typename VALUE2 >
        quantity< UNIT, decltype( VALUE() + VALUE2()) > operator-( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                "quantity<>: minus operation of different unit is not allowed!");
            return quantity< UNIT, decltype( VALUE() + VALUE2()) >( value - q.as< UNIT >());
        }
        
        template< typename UNIT2, typename VALUE2 >
        quantity &operator+=( quantity< UNIT2, VALUE2 > const &q)
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                "quantity<>: plus operation of different unit is not allowed!");
            value -= q.as< UNIT >();
            return *this;
        }
        
        template< typename UNIT2, typename VALUE2 >
        quantity &operator-=( quantity< UNIT2, VALUE2 > const &q)
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                "quantity<>: minus operation of different unit is not allowed!");
            value -= q.as< UNIT >();
            return *this;
        }
        
        quantity &operator++()
        {
            ++ value;
            return *this;
        }
        
        quantity operator++( int n)
        {
            quantity q( value ++);
            return q;
        }
        
        quantity &operator--()
        {
            -- value;
            return *this;
        }
        
        quantity operator--( int n)
        {
            quantity q( value --);
            return q;
        }
        
        template< typename UNIT2 >
        VALUE &as()
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: retrieve value by wrong unit!");
            return value;
        }
        
        template< typename UNIT2 >
        VALUE as() const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: retrieve value by wrong unit!");
            return value;
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator==( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value == q.as< UNIT >();
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator<( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value < q.as< UNIT >();
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator<=( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value <= q.as< UNIT >();
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator>( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value > q.as< UNIT >();
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator>=( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value >= q.as< UNIT >();
        }
        
        template< typename UNIT2, typename VALUE2 >
        bool operator!=( quantity< UNIT2, VALUE2 > const &q) const
        {
            static_assert( meta_function::is_same< UNIT, UNIT2 >::value,
                    "quantity<>: should not compare with different unit!");
            return value != q.as< UNIT >();
        }
        
        private:
            VALUE value;
    }; // template class quantity

    namespace metric_system
    {
        struct Meter {};
        typedef Meter Metre;
        
        struct KiloMeter{};
        typedef KiloMeter KiloMetre;
        
        struct CentiMeter{};
        typedef CentiMeter CentiMetre;
        
        struct SquareMeter {};
        typedef SquareMeter SquareMetre;
        
        // add more when needed ...
    }
    
    namespace britsh_system
    {
        struct Inch {};
        struct Foot {};
        struct Mile {};
    }

} // namespace util

#endif
