
#include <sstream>
#include "query_maker.h"

using namespace std;
using namespace query_maker;
using namespace _query_maker_inner;

Factor::Factor()
    : _type( NONE)
{
}

Factor::Factor( std::string const &str, Type type)
    : _str( str), _type( type)
{
}

Factor::Factor( Factor const &f)
    : _str( f._str), _type( f._type)
{
}

Factor::Factor( string const &column, string const &symbol, string const &value)
{
    string chomped_column( chomp( column));
    string chomped_symbol( chomp( symbol));
    if ( chomped_column.size() && chomped_symbol.size()) {
        _type = PRIMITIVE;
        ostringstream oss;
        oss << '`' << chomped_column << "` " << chomped_symbol << " '" << value << "'";
        _str = oss.str();
    } else
        _type = NONE;
}

Factor::Factor( string const &column, string const &symbol, int value)
{
    string chomped_column( chomp( column));
    string chomped_symbol( chomp( symbol));
    if ( chomped_column.size() && chomped_symbol.size()) {
        _type = PRIMITIVE;
        ostringstream oss;
        oss << '`' << chomped_column << "` " << chomped_symbol << ' ' << value;
        _str = oss.str();
    } else
        _type = NONE;
}

Factor::Factor( string const &column, string const &symbol, float value)
{
    string chomped_column( chomp( column));
    string chomped_symbol( chomp( symbol));
    if ( chomped_column.size() && chomped_symbol.size()) {
        _type = PRIMITIVE;
        ostringstream oss;
        oss << '`' << chomped_column << "` " << chomped_symbol << ' ' << value;
        _str = oss.str();
    } else
        _type = NONE;
}

Factor &
Factor::operator=( Factor const &f)
{
    _type = f._type;
    _str = f._str;
    return *this;
}

Factor
Factor::operator&( Factor const &f) const
{
    if ( _type == NONE)
        return f;
    if ( f._type == NONE)
        return *this;

    ostringstream oss;
    if ( _type == OR)
        oss << "( " << _str << " )";
    else
        oss << _str;
    oss << " AND ";
    if ( f._type == OR)
        oss << "( " << f._str << " )";
    else
        oss << f._str;
    return Factor( oss.str(), AND);
}

Factor &
Factor::operator&=( Factor const &f)
{
    return operator=( operator&( f));
}

Factor
Factor::operator|( Factor const &f) const
{
    if ( _type == NONE)
        return f;
    if ( f._type == NONE)
        return *this;

    ostringstream oss;
    if ( _type == AND)
        oss << "( " << _str << " )";
    else
        oss << _str;
    oss << " OR ";
    if ( f._type == AND)
        oss << "( " << f._str << " )";
    else
        oss << f._str;
    return Factor( oss.str(), OR);
}

Factor &
Factor::operator|=( Factor const &f)
{
    return operator=( operator|( f));
}

string const &
Factor::to_string() const
{
    return _str;
}

