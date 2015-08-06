#include <errno.h>
#include <stdio.h>//printf
#include <stdlib.h>//atoi
#include <string.h>//for memset,memcpy,strlen
#include "big_integer.h"
#include "memory_wrapper.h"

#define CARRY_BIT_LIMIT 10000
#define DEFAULT_SIZE 10

#define NEGATIVE 1
#define POSITIVE 0
#define TEMPORARY 1
#define PERSISTENT 0
#define ERROR 1
bool
is_zero( BigInteger * bigint)
{
    for ( int i = 0; i < bigint->size; i++)
        if( bigint->data[ i] != 0)
            return false;
    return true;
}

BigInteger*
_create( size_t size, int is_negative, int is_temporary) {
    BigInteger *bigint = NULL;
    errno = 0;
    bigint = MALLOC( sizeof( BigInteger));
    if( bigint == NULL)
        return NULL;
    size = ( size > 0)? size: DEFAULT_SIZE;
    bigint->data = MALLOC( size * sizeof( unsigned));
    if( bigint->data == NULL) {
        FREE( bigint);
        return NULL;
    }
    memset( bigint->data, 0, size * sizeof( unsigned));
    bigint->is_negative  = is_negative;
    bigint->is_temporary = is_temporary;
    bigint->is_nan = 0;
    bigint->is_inf = 0;
    bigint->size = size;
    return bigint;
}

int
_resize( BigInteger *bigint, size_t size) {
    if( size > bigint->size) {
        errno = 0;
        unsigned *ptr = REALLOC( bigint->data, size * sizeof( unsigned));
        if( ptr) {
            bigint->data = ptr;
            bigint->size = size;
        } else {
            return errno;
        }
    }
    return 0;
}

int
_assign_without_destroy( BigInteger *target, BigInteger* source) {
    if( target == source)
        return 0;
    if( target == NULL || source == NULL)
        return ERROR;
    target->is_inf = source->is_inf;
    target->is_nan = source->is_nan;
    target->is_negative = source->is_negative;
    if( is_zero( source)) {
        memset( target->data, 0, target->size * sizeof( unsigned));
        return 0;
    }
    size_t _size = source->size;
    while( _size > 0 && source->data[ _size - 1] == 0 )
        _size--;
    if( _resize( target, _size)) {
        return errno;
    }
    memset( target->data, 0, target->size * sizeof( unsigned));
    memcpy( target->data, source->data, _size * sizeof( unsigned));
    return 0;
}

bool
_abs_less( BigInteger *left, BigInteger *right) {
    size_t _actual_left_size = left->size;
    while( _actual_left_size - 1 > 0 &&
            left->data[ _actual_left_size - 1] == 0)
        _actual_left_size--;
    size_t _actual_right_size = right->size;
    while( _actual_right_size - 1 > 0 &&
            right->data[ _actual_right_size - 1] == 0)
        _actual_right_size--;
    if( _actual_left_size != _actual_right_size) {
        return _actual_left_size < _actual_right_size;
    } else {
        while( _actual_left_size - 1> 0
              && left->data[ _actual_left_size - 1 ] == right->data[ _actual_right_size  - 1])
            _actual_left_size--;
        return left->data[ _actual_left_size - 1 ] < right->data[ _actual_left_size  - 1];
    }
}

int
_multiply( BigInteger *left, BigInteger *right, BigInteger *result, BigInteger *temp) {
    size_t _actual_left_size = left->size;
    size_t _actual_right_size = right->size;
    //calculate actual size
    while( _actual_left_size - 1 > 0
          && left->data[ _actual_left_size - 1] == 0)
        _actual_left_size--;
    while( _actual_right_size - 1 > 0
          && right->data[ _actual_right_size - 1] == 0)
        _actual_right_size--;
    for( size_t i = 0; i < _actual_left_size; i++) {
        for( size_t j = 0; j < _actual_right_size; j++) {
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            unsigned value = left->data[ i] * right->data[ j];
            temp->data[ i + j] = value % CARRY_BIT_LIMIT;
            temp->data[ i + j + 1] = value / CARRY_BIT_LIMIT;
            if( big_integer_assign( result, big_integer_add( result, temp)))
                return ERROR;
        }
    }
    return 0;
}

int
_divide( BigInteger *dividend, BigInteger *divisor, BigInteger *quotient, BigInteger *remainder) {
    size_t _actual_dividend_size = dividend->size;
    size_t _actual_divisor_size = divisor->size;
    if( _abs_less( dividend, divisor))
        if( remainder)
            return _assign_without_destroy( remainder, dividend);
    //calculate actual size
    while( _actual_dividend_size - 1 > 0
            && dividend->data[ _actual_dividend_size - 1] == 0) 
        _actual_dividend_size--;
    while( _actual_divisor_size - 1 > 0
            && divisor->data[ _actual_divisor_size - 1] == 0)
        _actual_divisor_size--;
    //create temporary obj
    bool need_free_quotient = false, need_free_remainder =false;
    if( quotient == NULL) {
        quotient = _create( dividend->size, POSITIVE, PERSISTENT);
        need_free_quotient = true;
    }
    if( remainder == NULL) {
        remainder = _create( divisor->size, POSITIVE, PERSISTENT);
        need_free_remainder = true;
    }
    //calculate
    BigInteger *middle_number = _create( divisor->size, POSITIVE, PERSISTENT);
    if( middle_number == NULL)
        goto FINAL;
    BigInteger *product = _create( _actual_dividend_size + _actual_divisor_size, POSITIVE, PERSISTENT);
    if( product == NULL)
        goto FREE_MIDDLE;
    BigInteger *temp = _create( _actual_dividend_size + _actual_divisor_size, POSITIVE, PERSISTENT);
    if( temp == NULL)
        goto FREE_PRODUCT;
    _assign_without_destroy(remainder, dividend);
    remainder->is_negative = POSITIVE;
    unsigned *_original_data = remainder->data;
    size_t _original_size = remainder->size;
    long long remain_size = _actual_dividend_size - _actual_divisor_size;
    for( ; remain_size >= 0; remain_size-- ) {
        remainder->data = _original_data + remain_size;
        remainder->size = _original_size - remain_size;
        if( _abs_less( remainder, divisor))
            continue;
        unsigned lower = 0, middle = 0, upper = CARRY_BIT_LIMIT + 1;
        do {
            memset( middle_number->data, 0, middle_number->size * sizeof( unsigned));
            //if( lower == upper - 1)
            //    lower = upper;
            middle = ( lower + upper) / 2 ;
            if( middle == CARRY_BIT_LIMIT)
                middle_number->data[ 1] = 1;
            else
                middle_number->data[ 0] = middle;
            memset( product->data, 0, product->size * sizeof( unsigned));
            _multiply( divisor, middle_number, product, temp);
            if( _abs_less( remainder, product)) {
                upper = middle;
                continue;
            }
            if( big_integer_assign( temp, big_integer_minus( remainder, product)))
                goto FREE;
            if( is_zero(temp))
                break;
            if( !_abs_less( temp, divisor)) {
                if( !_abs_less( divisor, temp)) {
                    middle++;
                    memset( temp->data, 0, temp->size * sizeof( unsigned));
                    break;
                }
                lower = middle;
                continue;
            }
            break;
        }while( lower < upper);
        _assign_without_destroy(remainder, temp);
        quotient->data[ remain_size ] = middle;
    }
FREE:
    big_integer_destroy( temp);
FREE_PRODUCT:
    big_integer_destroy( product);
FREE_MIDDLE:
    big_integer_destroy( middle_number);
FINAL:
    if( need_free_quotient)
        big_integer_destroy( quotient);
    if( need_free_remainder)
        big_integer_destroy( remainder);
    return 0;
}

//interface function
bool
is_nan( BigInteger *bigint)
{
    if( bigint == NULL) return false;
    return  bigint->is_nan;
}

bool
is_inf( BigInteger *bigint)
{
    if( bigint == NULL) return false;
    return  bigint->is_inf;
}

bool
is_temporary( BigInteger *bigint)
{
    if( bigint == NULL) return false;
    return  bigint->is_temporary;
}

bool
is_normal( BigInteger *bigint)
{
    if( bigint == NULL) return false;
    return !is_nan( bigint) && !is_inf( bigint);
}

bool
is_negative( BigInteger *bigint)
{
    if( bigint == NULL) return false;
    return bigint->is_negative;
}

BigInteger *
big_integer_create( size_t size) {
    BigInteger *bigint = NULL;
    errno = 0;
    bigint = MALLOC( sizeof( BigInteger));
    if( bigint == NULL && errno)
        goto FINAL;
    size = ( size > 0)? size: DEFAULT_SIZE;
    bigint->data = MALLOC( size * sizeof( unsigned));
    errno = 0;
    if( bigint->data == NULL && errno) {
        FREE( bigint);
        goto FINAL;
    }
    memset( bigint->data, 0, size * sizeof( unsigned));
    bigint->is_negative  = 0;
    bigint->is_temporary = 0;
    bigint->is_nan = 0;
    bigint->is_inf = 0;
    bigint->size = size;
FINAL:
    return bigint;
}

void
big_integer_init( BigInteger* bigint, char *value) {
    size_t size = strlen( value);
    bool is_nagative = false;
    if( value[ 0] == '+' || value[ 0] == '-') {
        is_nagative = ( value[ 0] == '-');
        value++;
        size--;
    }
    bigint->is_negative = is_nagative;
    char buffer[ 12];
    value += size;
    for( size_t idx = 0; idx < bigint->size && size > 0 ; idx ++) {
        size_t len = size > 4 ? 4: size;
        value -= len;
        memset( buffer, 0, 12);
        memcpy( buffer,value, len);
        bigint->data[ idx] = atoi( buffer);
        size -= len;
    }
    bigint->is_inf = 0;
    bigint->is_nan = 0;
}

int big_integer_assign( BigInteger *target, BigInteger *source) {
    if( target == source )
        return 0;
    if( target == NULL || source == NULL)
        return 1;
    int result = _assign_without_destroy( target, source);
    if( source && source->is_temporary)
        big_integer_destroy( source);
    return result;
}

void 
big_integer_destroy( BigInteger *bigint) {
    if( bigint) {
        if( bigint->data)
            FREE( bigint->data);
        FREE( bigint);
    }
}

void
big_integer_output( BigInteger *bigint) {
    if( bigint == NULL) {
        puts( "null pointer");
    }
    if( bigint->is_nan) {
        puts( "nan");
        return;
    }
    if( bigint->is_inf) {
        puts( "inf");
        return;
    }
    if( bigint->is_negative)
        putchar( '-');
    size_t _actul_size = bigint->size;
    while( _actul_size > 0 && bigint->data[ _actul_size - 1 ] == 0)
        _actul_size--;
    for( size_t idx = _actul_size; idx > 0; idx--) {
        printf( "%0.4u", bigint->data[ idx - 1]);
    }
    
    puts("");
}

BigInteger*
big_integer_add( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    if( left->is_negative != right->is_negative) {
        right->is_negative = !right->is_negative;
        return big_integer_minus( left, right);
    }
    if( is_temporary( left)) {
        result = left;
        _resize( left, right->size);
    } else if( is_temporary( right)) {
        result = right;
        _resize( right, left->size);
    } else {
        size_t size = left->size > right->size ? left->size: right->size;
        result = _create( size, left->is_negative, TEMPORARY);
        if( result == NULL && errno )
            goto FINAL;
    }
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }
    size_t idx = 0;
    unsigned carry_bit = 0;
    for( ; idx < left->size && idx < right->size; idx++) {
        result->data[ idx] = left->data[ idx] + right->data[ idx] + carry_bit;
        if( result->data[ idx] > CARRY_BIT_LIMIT  ) {
            result->data[ idx] -= CARRY_BIT_LIMIT;
            carry_bit = 1;
        }else {
            carry_bit = 0;
        }
    }
    while( carry_bit && idx < result->size) {
        result->data[ idx] =  carry_bit;
        if( result->data[ idx] > CARRY_BIT_LIMIT  ) {
            result->data[ idx] -= CARRY_BIT_LIMIT;
            carry_bit = 1;
        }else {
            carry_bit = 0;
        }
        idx++;
    }
    result->is_negative = left->is_negative;
FINAL:
    if( is_temporary( left) && result != left)
        big_integer_destroy( left);
    if( is_temporary( right) && result != right)
        big_integer_destroy( right);
    return result;
}


BigInteger*
big_integer_minus( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }
    if( left->is_negative != right->is_negative) {
        right->is_negative = !right->is_negative;
        return big_integer_add( left, right);
    }
    if( _abs_less( left, right)) {
        result = big_integer_minus( right, left);
        result->is_negative = !result->is_negative;
        return result;
    }
    if( is_temporary( left)) {
        result = left;
        _resize( result, right->size);
    } else if( is_temporary( right)) {
        result = right;
        _resize( result, left->size);
    } else {
        size_t size = left->size > right->size ? left->size: right->size;
        result = _create( size, left->is_negative, TEMPORARY);
        if( result == NULL && errno)
            goto FINAL;
    }
    size_t idx = 0;
    unsigned borrow_bit = 0;
    for( ; idx < left->size && idx < right->size; idx++) {
        if( left->data[ idx] < right->data[ idx] + borrow_bit) {
            result->data[ idx] = CARRY_BIT_LIMIT + left->data[ idx] - right->data[ idx] - borrow_bit;
            borrow_bit = 1;
        } else {
            borrow_bit = 0;
            result->data[ idx] = left->data[ idx] - right->data[ idx] - borrow_bit;
        }
    }
    while( borrow_bit && idx < result->size) {
        if( left->data[ idx] < borrow_bit) {
            result->data[ idx] = CARRY_BIT_LIMIT + left->data[ idx] - borrow_bit;
            borrow_bit = 1;
        }else {
            result->data[ idx] = left->data[ idx] - borrow_bit;
            borrow_bit = 0;
        }
        idx++;
    }
FINAL:
    if( is_temporary( left) && result != left)
        big_integer_destroy( left);
    if( is_temporary( right) && result != right)
        big_integer_destroy( right);
    return result;
}


BigInteger *
big_integer_multiply( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    size_t size = left->size + right->size;
    result = _create( size, POSITIVE, TEMPORARY);
    if( result == NULL && errno)
        goto FINAL;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }
    BigInteger *temp= _create( size, POSITIVE, PERSISTENT);
    if( temp == NULL && errno) {
        big_integer_destroy(result);
        result = NULL;
        goto FINAL;
    }
    
    _multiply( left, right, result, temp);
    int symbol = left->is_negative != right->is_negative ? NEGATIVE : POSITIVE;
    result->is_negative = symbol;
    big_integer_destroy( temp);
FINAL:
    if( result)
        result->is_temporary = TEMPORARY;
    if( is_temporary( left))
        big_integer_destroy( left);
    if( is_temporary( right))
        big_integer_destroy( right);
    return result;
}


BigInteger *
big_integer_divide( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    errno = 0;
    result = _create( left->size, POSITIVE, PERSISTENT);
    if( result == NULL && errno)
        goto FINAL;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }else if( is_zero( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_zero( left)) {
        goto FINAL;
    }
    if( _divide( left, right, result, NULL)) {
        big_integer_destroy( result);
        result = NULL;
    }else {
        int symbol = left->is_negative != right->is_negative;
        result->is_negative = symbol;
    }
    
FINAL:
    if( result)
        result->is_temporary = TEMPORARY;
    if( left&&is_temporary( left) )
        big_integer_destroy( left);
    if( right&&is_temporary( right) )
        big_integer_destroy( right);
    return result;
}


BigInteger *
big_integer_mod( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    result = _create( right->size, POSITIVE, PERSISTENT);
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }else if( is_zero( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_zero( left))
        goto FINAL;
    if( _divide( left, right, NULL, result)) {
        big_integer_destroy( result);
        result = NULL;
    }else {
        int symbol = left->is_negative != right->is_negative;
        result->is_negative = symbol;
    }
    
FINAL:
    if( result)
        result->is_temporary = TEMPORARY;
    if( is_temporary( left) && result != left)
        big_integer_destroy( left);
    if( is_temporary( right) && result != right)
        big_integer_destroy( right);
    return result;
}


bool 
big_integer_less( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result = false;
    else if( left->is_negative && !right->is_negative)
        result = true;
    else if( !left->is_negative && right->is_negative)
        result = false;
    else if( left->is_negative)
        result = _abs_less( right, left);
    else
        result = _abs_less( left, right);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}


bool 
big_integer_less_equal( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right)
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result = true;
    else if( left->is_negative && !right->is_negative)
        result = true;
    else if( !left->is_negative && right->is_negative)
        result = false;
    else if( left->is_negative)
        result = !_abs_less( left, right);
    else
        result = !_abs_less( right, left);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}


bool 
big_integer_greater( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result  = false;
    else if( left->is_negative && !right->is_negative)
        result = false;
    else if( !left->is_negative && right->is_negative)
        result = true;
    else if( left->is_negative)
        result = _abs_less( left, right);
    else
        result = _abs_less( right, left);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}

bool 
big_integer_greater_equal( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result  = true;
    else if( left->is_negative && !right->is_negative)
        result = false;
    else if( !left->is_negative && right->is_negative)
        result = true;
    else if( left->is_negative)
        result = !_abs_less( right, left);
    else
        result = !_abs_less( left, right);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}

bool 
big_integer_equal( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result  = true;
    else if( left->is_negative != right->is_negative)
        result = false;
    else 
        result = !_abs_less( right, left) && !_abs_less( left, right);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}


bool 
big_integer_not_equal( BigInteger *left, BigInteger *right) {
    bool result = false;
    if( left == NULL || right == NULL)
        result = false;
    else if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    else if( is_zero( left) && is_zero( right))
        result  = false;
    else if( left->is_negative != right->is_negative)
        result = true;
    else 
        result = _abs_less( right, left) || _abs_less( left, right);
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}





