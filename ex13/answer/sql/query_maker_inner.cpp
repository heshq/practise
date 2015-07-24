#include <sstream>
#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

namespace query_maker
{
    namespace _query_maker_inner
    {
        string chomp( string const &str)
        {
            int begin = 0, end = str.size();
            while ( begin < end && str[ begin] == ' ')
                begin ++;
            while ( begin < end && str[ end - 1] == ' ')
                end --;
            return str.substr( begin, end - begin);
        }
    }
}

void
SetColumn::_set( string const &column, int value)
{
    string c( chomp( column));
    if ( c.size()) {
        ostringstream oss;
        oss << value;
        _columns[ c] = oss.str();
    }
}

void
SetColumn::_set( string const &column, float value)
{
    string c( chomp( column));
    if ( c.size()) {
        ostringstream oss;
        oss << value;
        _columns[ c] = oss.str();
    }
}

void
SetColumn::_set( string const &column, string const &value)
{
    string c( chomp( column));
    if ( c.size()) {
        ostringstream oss;
        oss << '\'' << value << '\'';
        _columns[ c] = oss.str();
    }
}

HasFactor::HasFactor()
{
}

void
HasFactor::_where( Factor const &f)
{
    _factor = f;
}

bool
HasFactor::_has_factor() const
{
    return _factor._type != Factor::NONE;
}

