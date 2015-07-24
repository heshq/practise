#include <sstream>

#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

void
Delete::_build()
{
    ostringstream oss;
    oss << "delete from " << _table;
    if ( _has_factor())
        oss << " where " << _factor.to_string();
    _result = oss.str();
}

Delete &
Delete::table( std::string const &table)
{
    _set_table( table);
    _dirty = true;
    return *this;
}

Delete &
Delete::where( Factor const &factor)
{
    _where( factor);
    _dirty = true;
    return *this;
}

template< typename T >
Delete &
Delete::where( string const &column, string const &symbol, T value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}

template Delete &Delete::where< string const &>( string const &, string const &, string const &);
template Delete &Delete::where< int >( string const &, string const &, int);
template Delete &Delete::where< float >( string const &, string const &, float);
template Delete &Delete::where< char const * >( string const &, string const &, char const *);

bool
Delete::check() const
{
    return _table.size();
}

