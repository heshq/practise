#include <iostream>
#include <iterator>     // std::begin(), std::end()
#include <list>
#include <vector>

#include "binary.h"
#include "find_most.h"
#include "prime_table.h"
#include "safe_compare.h"
#include "unit.h"

using namespace std;

void test_binary()
{
    using util::binary;
#define TEST( x) std::cout << "'" #x "' : " << binary< x >::value << std::endl
    TEST( 1);
    TEST( 10);
    TEST( 11);
    TEST( 110);
    TEST( 1000);
    TEST( 1111);
    TEST( 1111111111);
    TEST( 10000000000);
    //TEST( 121);
#undef TEST
}

void test_find_most()
{
    using util::find_largest;
    using util::find_smallest;
    {
        int arr[] = { 1, 3, 5, 7, -6, -4, -2, 0};
        auto it = find_largest( begin( arr), end( arr));
        cout << "Largest  : " << *it << endl;
        it = find_smallest( begin( arr), end( arr));
        cout << "Smallest : " << *it << endl;
    }
    {
        struct decimal_less {
            bool operator()( float a, float b)
            {
                int integer_a = a, integer_b = b;
                return ( a - integer_a) < ( b - integer_b);
            }
        };
        vector<float> vec{ 1.5, 2.4, 3.3, 4.2, 5.1};
        auto it = find_largest( begin( vec), end( vec), decimal_less());
        cout << "Largest  : " << *it << endl;
        it = find_smallest( begin( vec), end( vec), decimal_less());
        cout << "Smallest : " << *it << endl;
    }
    {
        list<bool> l;
        auto it = find_largest( l.begin(), l.end());
        if ( it == l.end())
            cout << "Largest  : Not Found" << endl;
        it = find_smallest( l.begin(), l.end());
        if ( it == l.end())
            cout << "Smallest : Not Found" << endl;
    }
}

void test_safe_compare()
{
    using util::less;
    using util::less_equal;
    using util::greater;
    using util::greater_equal;
    using util::equal;
    using util::not_equal;
    
#define TEST( a, b, op_normal, op_safe) { \
            cout << a << ' ' << #op_normal << ' ' << b << " : " \
                << ( a op_normal b ? "True" : "False") << endl; \
            cout << #op_safe << "( " << a << ", " << b << " ) : " \
                << ( op_safe( a, b) ? "True" : "False") << endl; \
        }

    unsigned long long_unsigned = -1;
    short short_negative = -1;
    
    TEST( short_negative, long_unsigned, <,  less);
    TEST( short_negative, long_unsigned, <=, less_equal);
    TEST( short_negative, long_unsigned, >,  greater);
    TEST( short_negative, long_unsigned, >=, greater_equal);
    TEST( short_negative, long_unsigned, ==, equal);
    TEST( short_negative, long_unsigned, !=, not_equal);
    
    long long_negative = -1;
    TEST( short_negative, long_negative, ==, equal);
    
    double a = 2.0 / 3;
    float b = 2.0 / 3;
    TEST( a, b, <,  less);
    TEST( a, b, <=, less_equal);
    TEST( a, b, ==, equal);
    
#undef TEST
}


void test_prime_table()
{
    static util::prime_table< 1000 > _table;
    bool *table = reinterpret_cast< bool * >( &_table);
    
    int const BEGIN = 2;
    int const END = 100;
    
    cout << "Prime numbers between " << BEGIN << " and " << END << " are:" << endl;
    
    for ( int i = 2; i < 100; i ++)
        if ( table[ i])
            cout << ' ' << i;
            
    cout << endl;
}

void test_unit()
{
    using util::quantity;
    using util::metric_system::Meter;
    using util::metric_system::SquareMeter;
    using util::britsh_system::Inch;
    
    quantity< Meter, float > length = 1.23;
    quantity< Meter, int > width;
    quantity< Inch, float > tmp;
    
    width = length;
    //tmp = length;
    
    if ( width == length) cout << "MCO: System OK." << endl;

    //if ( tmp == length) cout << "MCO: Crush on Mars!" << endl;
    
    
    tmp.as< Inch >() = length.as< Meter >() * 39.37;
    cout << length.as< Meter >() << " meter = " << tmp.as< Inch >() << " inch" << endl;
    
    width.as< Meter >() = 20;
    quantity< SquareMeter, float > const area =
                                                width.as< Meter >()
                                                * length.as< Meter >();
    cout << "area is : " << area.as< SquareMeter >() << " m^2" << endl;
}

int main()
{
    cout << "========== binary ===========" << endl;
    test_binary();
    cout << "========= find_most =========" << endl;
    test_find_most();
    cout << "======== safe_compare =======" << endl;
    test_safe_compare();
    cout << "======== prime_table ========" << endl;
    test_prime_table();
    cout << "=========== unit ============" << endl;
    test_unit();
    return 0;
}

