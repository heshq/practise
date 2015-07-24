
#include <cstdarg>
#include <cstring>  // strerror()
#include <cerrno>
#include <new>      // nothrow

#include "format.h"

using namespace std;

static const ssize_t INIT_BUFFER_SIZE = 32;

string format( char const *fmt, ...)
{
    int ret;
    int err;
    va_list args;

    char *buffer = new( nothrow) char[ INIT_BUFFER_SIZE];
    if ( ! buffer)
        goto ALLOC_FAIL;

    va_start( args, fmt);
    errno = 0;
    ret = vsnprintf( buffer, INIT_BUFFER_SIZE, fmt, args);
    err = errno;
    va_end( args);

    if ( ret < 0)
        goto PRINTF_FAIL;
    else if ( ret < INIT_BUFFER_SIZE)
        goto OK;

    delete[] buffer;
    buffer = new( nothrow) char[ ret];
    if ( ! buffer)
        goto ALLOC_FAIL;

    va_start( args, fmt);
    errno = 0;
    ret = vsnprintf( buffer, ret, fmt, args);
    err = errno;
    va_end( args);

    if ( ret < 0)
        goto PRINTF_FAIL;

OK: {
        string result( buffer, 0, ret);
        delete[] buffer;
        return result;
    }

ALLOC_FAIL: {
        string msg( "format() failed: cannot alloc memory for buffer");
        throw msg;
    }

PRINTF_FAIL: {
        delete[] buffer;
        string msg( "format() failed: vsnprintf() failed: ");
        msg += strerror( err);
        throw msg;
    }
}

