#include <iostream>
#include <string>
#include <vector>
#include "query_maker.h"

using namespace std;
using namespace query_maker;

struct Condition {
    string column;
    enum OPTR {
        LESS_THAN, GREATER_THAN, EQUAL_TO
    } optr;
    enum VALUE_TYPE {
        INT, FLOAT, STRING
    } type;
    union {
        int i;
        float f;
        char const *s;
    } value;
    template< typename T > void set_value( T v) {}
    template< typename T >
    Condition( string column, OPTR optr, T v)
        : column( column), optr( optr)
    {
        set_value( v);
    }
    char const *optr_str() const
    {
        switch ( optr) {
            case GREATER_THAN:  return ">";
            case LESS_THAN:     return "<";
            case EQUAL_TO:      return "=";
            default:            return "";
        }
    }
};
template<> void Condition::set_value< int >( int v) { value.i = v; type = INT;}
template<> void Condition::set_value< float >( float v) { value.f = v; type = FLOAT;}
template<> void Condition::set_value< char const * >( char const *v) { value.s = v; type = STRING;}

int main()
{
    Select s1;
    s1.table( "Student")
        .column( " name, age ,gender,score ")
        .where(
                Factor( "gender", "=", "female")
                & Factor( "score", ">=", 60.0f)
                & ( Factor( "age", "<", 12) | Factor( "age", ">", 24))
        ).order_by( "score").order_by( "age").order_by( " score ").desc();
    cout << (string)s1 << endl;

    cout << (string)Select( " Student") << endl;

    cout << (string)Insert( "Student")
                .set( "name", "John Ming")
                .set( "age ", 18)
                .set( " score ", 99.9f)
        << endl;

    cout << (string)Update( " Student ")
                .where( "name ", "like", "john %")
                .set( "age", 20)
                .set( "gender", "male")
        << endl;

    string column( "age");
    string optr( ">=");
    int value = 24;
    cout << (string)Delete( "Student").where( column, optr, value) << endl;

    // simulate user-defined search:
    vector< Condition > conditions;
    conditions.push_back( Condition( "age",     Condition::GREATER_THAN,    24));
    conditions.push_back( Condition( "score",   Condition::LESS_THAN,       60.0f));
    conditions.push_back( Condition( "gender",  Condition::EQUAL_TO,        "male"));

    vector< string > columns = { "name", "grade", "class"};

    Select s3( "Student");
    Factor factor;
    for ( auto it = conditions.begin(); it != conditions.end(); ++ it)
        switch ( it->type) {
            case Condition::INT:
                factor &= Factor( it->column, it->optr_str(), it->value.i); break;
            case Condition::FLOAT:
                factor &= Factor( it->column, it->optr_str(), it->value.f); break;
            case Condition::STRING:
                factor &= Factor( it->column, it->optr_str(), it->value.s); break;
        }
    s3.where( factor);
    for ( auto it = columns.begin(); it != columns.end(); ++ it)
        s3.column( *it);

    cout << (string)s3 << endl;

    return 0;
}

