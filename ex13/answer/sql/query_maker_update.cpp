#include <sstream>
#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

void
Update::_build()
{
    ostringstream oss;
    oss << "update " << _table;
    if ( _columns.size()) {
        oss << " set ";
        auto it = _columns.begin();
        oss << '`' << it->first << "`=" << it->second;
        for ( ++ it; it != _columns.end(); ++ it)
            oss << ", `" << it->first << "`=" << it->second;
    }
    if ( _has_factor())
        oss << " where " << _factor.to_string();
    _result = oss.str();
}

Update &
Update::table( string const &table)
{
    _set_table( table);
    _dirty = true;
    return *this;
}

template< typename T >
Update &
Update::set( string const &column, T value)
{
    _set( column, value);
    _dirty = true;
    return *this;
}

template Update &Update::set< string const & >( string const &, string const &);
template Update &Update::set< char const * >( string const &, char const *);
template Update &Update::set< int >( string const &, int);
template Update &Update::set< float >( string const &, float);

bool
Update::check() const
{
    return _table.size() > 0 && _columns.size() > 0;
}

Update &
Update::where( Factor const &f)
{
    _where( f);
    _dirty = true;
    return *this;
}

template< typename T>
Update &
Update::where( string const &column, string const &symbol, T value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}

template Update &Update::where< string const &>( string const &, string const &, string const &);
template Update &Update::where< char const * >( string const &, string const &, char const *);
template Update &Update::where< int >( string const &, string const &, int);
template Update &Update::where< float >( string const &, string const &, float);

