#include <sstream>
#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

void
Insert::_build()
{
    ostringstream oss;
    oss << "insert into " << _table;
    if ( _columns.size()) {
        oss << " (";
        auto it = _columns.begin();
        oss << '`' << it->first << '`';
        for ( ++ it; it != _columns.end(); ++ it)
            oss << ",`" << it->first << '`';

        oss << ") values (";

        it = _columns.begin();
        oss << it->second;
        for ( ++ it; it != _columns.end(); ++ it)
            oss << ',' << it->second;

        oss << ')';
    }
    _result = oss.str();
}

Insert &
Insert::table( string const &table)
{
    _set_table( table);
    _dirty = true;
    return *this;
}

template< typename T >
Insert &
Insert::set( string const &column, T value)
{
    _set( column, value);
    _dirty = true;
    return *this;
}

template Insert &Insert::set< string const &>( string const &, string const &);
template Insert &Insert::set< char const * >( string const &, char const *);
template Insert &Insert::set< int >( string const &, int);
template Insert &Insert::set< float >( string const &, float);

bool
Insert::check() const
{
    return _table.size() > 0 && _columns.size() > 0;
}


