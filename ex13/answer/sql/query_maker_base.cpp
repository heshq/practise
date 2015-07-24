
#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

QueryBase::QueryBase()
    : _dirty( true)
{
}

QueryBase::QueryBase( string const &table)
    : _dirty( true)
{
    _set_table( table);
}

QueryBase::~QueryBase()
{
}

void
QueryBase::_set_table( string const &table)
{
    _table = chomp( table);
}

string const &
QueryBase::table() const
{
    return _table;
}

string const &
QueryBase::to_string()
{
    if ( _dirty) {
        _build();
        _dirty = false;
    }
    return _result;
}

QueryBase::operator string()
{
    return to_string();
}

QueryBase::operator bool() const
{
    return check();
}

