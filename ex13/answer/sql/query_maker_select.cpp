#include <sstream>
#include <algorithm>    // find()

#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

void
Select::_build()
{
    ostringstream oss;
    oss << "select ";
    if ( _columns.size()) {
        auto it = _columns.begin();
        oss << '`' << *it << '`';
        for ( ++ it; it != _columns.end(); ++ it)
            oss << ",`" << *it << '`';
    } else
        oss << '*';
    oss << " from " << _table;
    if ( _has_factor())
        oss << " where " << _factor.to_string();
    if ( _orders.size()) {
        auto it = _orders.begin();
        oss << " order by `" << *it << '`';
        for ( ++ it; it != _orders.end(); ++ it)
            oss << ",`" << *it << '`';
        if ( ! _asc)
            oss << " desc";
    }
    _result = oss.str();
}

Select &
Select::table( std::string const &table)
{
    _set_table( table);
    _dirty = true;
    return *this;
}

Select &
Select::where( Factor const &factor)
{
    _where( factor);
    _dirty = true;
    return *this;
}

template< typename T >
Select &
Select::where( string const &column, string const &symbol, T value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}

template Select &Select::where< string const &>( string const &, string const &, string const &);
template Select &Select::where< char const * >( string const &, string const &, char const *);
template Select &Select::where< int >( string const &, string const &, int);
template Select &Select::where< float >( string const &, string const &, float);

/*
Select &
Select::where( string const &column, string const &symbol, string const &value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}

Select &
Select::where( string const &column, string const &symbol, int value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}

Select &
Select::where( string const &column, string const &symbol, float value)
{
    _where( Factor( column, symbol, value));
    _dirty = true;
    return *this;
}
*/

Select &
Select::asc()
{
    _asc = true;
    _dirty = true;
    return *this;
}

Select &
Select::desc()
{
    _asc = false;
    _dirty = true;
    return *this;
}

void
Select::_set_single_column( vector< string > &list, string const &str, size_t begin, size_t end)
{
    while ( begin < end && str[ begin] == ' ')
        begin ++;
    while ( begin < end && str[ end - 1] == ' ')
        end --;
    if ( begin < end) {
        string column( str.substr( begin, end - begin));
        if ( find( list.begin(), list.end(), column) == list.end()) {
            list.push_back( column);
            _dirty = true;
        }
    }
}

void
Select::_set_columns( vector< string > &list, string const &str)
{
    size_t begin = 0;
    size_t end;
    while ( ( end = str.find( ',', begin)) != string::npos) {
        _set_single_column( list, str, begin, end);
        begin = end + 1;
    }
    _set_single_column( list, str, begin, str.size());
}

Select &
Select::order_by( std::string const &column)
{
    _set_columns( _orders, column);
    return *this;
}

Select &
Select::column( std::string const &column)
{
    _set_columns( _columns, column);
    return *this;
}

bool
Select::check() const
{
    return _table.size();
}

