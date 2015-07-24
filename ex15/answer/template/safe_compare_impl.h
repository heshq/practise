#ifndef _SAFE_COMPARE_IMPL
#define _SAFE_COMPARE_IMPL

namespace util
{

    namespace traits
    {
        enum NumberType {
            SINGLE,
            DOUBLE,
            LONG_DOUBLE,
            INTEGER,
        };
        
        template< typename T1, typename T2, bool CHOOSE_LEFT >
        struct choose_type {
            typedef T1 type;
        };
        
        template< typename T1, typename T2>
        struct choose_type< T1, T2, false > {
            typedef T2 type;
        };
        
        // traits for every number type:
        template< typename T >
        struct number_traits {
            static bool const           is_unsigned = false;
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< char > {
#if CHAR_MIN < 0
            static bool const           is_unsigned = false;
#else
            static bool const           is_unsigned = true;
#endif
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< unsigned char > {
            static bool const           is_unsigned = true;
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< unsigned short > {
            static bool const           is_unsigned = true;
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< unsigned int > {
            static bool const           is_unsigned = true;
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< unsigned long > {
            static bool const           is_unsigned = true;
            static NumberType const     type_number = INTEGER;
        };

        template<>
        struct number_traits< unsigned long long > {
            static bool const           is_unsigned = true;
            static NumberType const     type_number = INTEGER;
        };
        
        template<>
        struct number_traits< float > {
            static bool const           is_unsigned = false;
            static NumberType const     type_number = SINGLE;
        };
        
        template<>
        struct number_traits< double > {
            static bool const           is_unsigned = false;
            static NumberType const     type_number = DOUBLE;
        };
        
        template<>
        struct number_traits< long double > {
            static bool const           is_unsigned = false;
            static NumberType const     type_number = LONG_DOUBLE;
        };
        
    } // namespace traits

    namespace safe_compare
    {
        // primary template is for comparing float number:
        template< typename T1, bool UNSIGNED1, typename T2, bool UNSIGNED2, typename USE_TYPE, bool IS_INTEGER >
        struct safe_compare {
            static bool less( T1 const &a, T2 const &b)
            {
                return USE_TYPE( a)  < USE_TYPE( b);
            }
            static bool less_equal( T1 const &a, T2 const &b)
            {
                return USE_TYPE( a) <= USE_TYPE( b);
            }
            static bool equal( T1 const &a, T2 const &b)
            {
                return USE_TYPE( a) == USE_TYPE( b);
            }
        };
        
        // specializations for comparing signed integer with unsigned integer:
        
        template< typename T1, typename T2, typename USE_TYPE > // T1 is signed, T2 is unsigned
        struct safe_compare< T1, false, T2, true, USE_TYPE, true > {
            static bool less( T1 const &a, T2 const &b)
            {
                return a < 0 ? true : a < b;
            }
            static bool less_equal( T1 const &a, T2 const &b)
            {
                return a < 0 ? true : a <= b;
            }
            static bool equal( T1 const &a, T2 const &b)
            {
                return a < 0 ? false : a == b;
            }
        };

        template< typename T1, typename T2, typename USE_TYPE > // T1 is unsigned, T2 is signed
        struct safe_compare< T1, true, T2, false, USE_TYPE, true > {
            static bool less( T1 const &a, T2 const &b)
            {
                return b < 0 ? false : a < b;
            }
            static bool less_equal( T1 const &a, T2 const &b)
            {
                return b < 0 ? false : a <= b;
            }
            static bool equal( T1 const &a, T2 const &b)
            {
                return b < 0 ? false : a == b;
            }
        };
        
        // specialization for comparing both-signed integer or both-unsigned integer
        template< typename T1, typename T2, bool UNSIGNED, typename USE_TYPE >
        struct safe_compare< T1, UNSIGNED, T2, UNSIGNED, USE_TYPE, true > {
            static bool less( T1 const &a, T2 const &b)
            {
                return a < b;
            }
            static bool less_equal( T1 const &a, T2 const &b)
            {
                return a <= b;
            }
            static bool equal( T1 const &a, T2 const &b)
            {
                return a == b;
            }
        };
    } // namespace safe_compare
    
    template< typename T1, typename T2 >
    bool less( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return safe_compare< T1, Traits1::is_unsigned, T2, Traits2::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::less( a, b);
    }

    template< typename T1, typename T2 >
    bool less_equal( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return safe_compare< T1, Traits1::is_unsigned, T2, Traits2::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::less_equal( a, b);
    }

    template< typename T1, typename T2 >
    bool greater( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return safe_compare< T2, Traits2::is_unsigned, T1, Traits1::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::less( b, a);
    }

    template< typename T1, typename T2 >
    bool greater_equal( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return safe_compare< T2, Traits2::is_unsigned, T1, Traits1::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::less_equal( b, a);
    }

    template< typename T1, typename T2 >
    bool equal( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return safe_compare< T1, Traits1::is_unsigned, T2, Traits2::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::equal( a, b);
    }

    template< typename T1, typename T2 >
    bool not_equal( T1 const &a, T2 const &b)
    {
        using namespace traits;
        using safe_compare::safe_compare;
        
        typedef number_traits< T1 > Traits1;
        typedef number_traits< T2 > Traits2;
        
        return ! safe_compare< T1, Traits1::is_unsigned, T2, Traits2::is_unsigned,
                                typename choose_type< T1, T2, Traits1::type_number < Traits2::type_number >::type,
                                Traits1::type_number == INTEGER && Traits2::type_number == INTEGER
                        >::equal( a, b);
    }
} // namespace util

#endif
