#include <errno.h>
#include <stdio.h>//printf
#include <stdlib.h>//atoi
#include <string.h>//for memset,memcpy,strlen
#include "big_integer.h"

#define CARRY_BIT_LIMIT 10000
#define DEFAULT_SIZE 10

int
_resize( BigInteger *bigint, size_t size) {
    if( size > bigint->size) {
        unsigned *ptr = realloc( bigint->data, size * sizeof( unsigned));
        if( ptr) {
            bigint->data = ptr;
            bigint->size = size;
        } else {
            big_integer_destroy( bigint);
        }
    }
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
    OBJ_TYPE _original = result->is_temporary;
    result->is_temporary = TEMPORARY_OBJ;
    for( size_t i = 0; i < left->size; i++) {
        for( size_t j = 0; j < right->size; j++) {
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            unsigned value = left->data[ i] * right->data[ j];
            temp->data[ i + j] = value % CARRY_BIT_LIMIT;
            temp->data[ i + j + 1] = value / CARRY_BIT_LIMIT;
            big_integer_add( result, temp);
        }
    }
    result->is_temporary = _original;
    return 0;
}

int
_divide( BigInteger *dividend, BigInteger *divisor, BigInteger *quotient, BigInteger *remainder) {
    if( quotient)
        memset( quotient->data, 0, quotient->size * sizeof( unsigned));
    if( remainder)
        memset( remainder->data, 0, remainder->size * sizeof( unsigned));
    int _actual_dividend_size = dividend->size;
    int _actual_divisor_size = divisor->size;
    //calculate actual size
    while( _actual_dividend_size - 1 >= 0 
            && dividend->data[ _actual_dividend_size - 1] == 0) 
        _actual_dividend_size--;
    if( _actual_dividend_size < 0)
        goto FINAL;
    while( _actual_divisor_size - 1 >= 0
            && divisor->data[ _actual_divisor_size - 1] == 0)
        _actual_divisor_size--;
    if( _actual_divisor_size < 0)
        goto FINAL;
    if( _actual_dividend_size < _actual_divisor_size) {
        if( remainder)
            memcpy( remainder->data, divisor->data, _actual_dividend_size * sizeof( unsigned));
        goto FINAL;
    }
    //create temporary obj
    bool need_free_quotient = false, need_free_remainder =false;
    bool _original_dividend_is_temporary = dividend->is_temporary;
    dividend->is_temporary = 0;
    bool _original_divisor_is_temporary = divisor->is_temporary;
    divisor->is_temporary = 0;
    if( quotient == NULL) {
        quotient = big_integer_create( dividend->size, false);
        big_integer_assign( quotient, dividend); 
        need_free_quotient = true;
    }
    bool _original_quotient_is_temporary = quotient->is_temporary;
    quotient->is_temporary = 0;
    if( remainder == NULL) {
        remainder = big_integer_create( divisor->size, false);
        need_free_remainder = true;
    }
    //calculate
    BigInteger *temp = big_integer_create( divisor->size, false);
    BigInteger *product = big_integer_create( _actual_dividend_size + _actual_divisor_size, false);
    BigInteger *temp2 = big_integer_create( _actual_dividend_size + _actual_divisor_size, false);
    divisor->is_negative = 0;
    big_integer_assign(remainder, dividend);
    unsigned *_original_data = remainder->data;
    size_t _original_size = remainder->size;
    int remain_size = _actual_dividend_size - _actual_divisor_size;
    for( ; remain_size >= 0; remain_size-- ) {
        remainder->data = _original_data + remain_size;
        remainder->size = _original_size - remain_size;
        if( _abs_less( remainder, divisor))
            continue;
        unsigned lower = 0, middle = 0, upper = CARRY_BIT_LIMIT;
        do {
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            if( lower == upper - 1)
                lower = upper;
            middle = ( lower + upper) / 2 ;
            if( middle == CARRY_BIT_LIMIT)
                temp->data[ 1] = 1;
            else
                temp->data[ 0] = middle;
            memset( product->data, 0, product->size * sizeof( unsigned));
            _multiply( divisor, temp, product, temp2);
            if( _abs_less( remainder, product)) {
                upper = middle;
                continue;
            }
            if( big_integer_assign( temp, big_integer_minus( remainder, product)))
                goto FINAL;
            if( !_abs_less( temp, divisor)) {
                lower = middle;
                continue;
            }
            break;
        }while( lower < upper);
        big_integer_assign(remainder, temp);
        quotient->data[ remain_size ] = middle;
    }
FINAL:
    big_integer_destroy( temp);
    if( need_free_quotient)
        big_integer_destroy( quotient);
    if( need_free_remainder)
        big_integer_destroy( remainder);
    dividend->is_temporary = _original_dividend_is_temporary;
    divisor->is_temporary = _original_divisor_is_temporary;
    return 0;
}

bool
is_zero( BigInteger * bigint)
{
    for ( int i = 0; i < bigint->size; i++)
        if( bigint->data[ i] != 0)
            return false;
    return true;
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
big_integer_create( size_t size, bool is_temporary) {
    BigInteger *bigint = malloc( sizeof( BigInteger));
    size = ( size > 0)? size: DEFAULT_SIZE;
    bigint->data = malloc( size * sizeof( unsigned));
    memset( bigint->data, 0, size * sizeof( unsigned));
    bigint->is_negative  = 0;
    bigint->is_temporary = is_temporary ? 1: 0;
    bigint->is_nan = 0;
    bigint->is_inf = 0;
    bigint->size = size;
    return bigint;
}

BigInteger*
big_integer_init( char *value) {
    size_t size = strlen( value);
    bool is_nagative = false;
    if( value[ 0] == '+' || value[ 0] == '-') {
        is_nagative = ( value[ 0] == '-');
        value++;
        size--;
    }
    BigInteger *result = big_integer_create( ( size + 3)/4, false);
    result->is_negative = is_nagative;
    char buffer[ 12];
    value += size;
    for( size_t idx = 0; idx < result->size ; idx ++) {
        value -= 4;
        memset( buffer, 0, 12);
        memcpy( buffer,value, size > 4 ? 4 : size);
        result->data[ idx] = atoi( buffer);
        size -= 4;
    }
    return result;
}

int big_integer_assign( BigInteger *target, BigInteger *source) {
    if( target == source )
        return 0;
    if( target == NULL || source == NULL)
        return 1;
    size_t _actual_source_size = source->size;
    if( is_zero( source)) {
        memset( target->data, 0, target->size);
        return 0;
    }
    while( _actual_source_size > 0 
            && source->data[ _actual_source_size - 1] == 0 )
        _actual_source_size--;
    _resize( target, _actual_source_size);
    /**if( errno) {
        if( source->is_temporary)
            big_integer_destroy( source);
        return 1;
    } else { */
        memset( target->data, 0, target->size * sizeof( unsigned));
        memcpy( target->data, source->data, _actual_source_size * sizeof( unsigned));
        if( source->is_temporary)
            big_integer_destroy( source);
        return 0;
    //}
}

void 
big_integer_destroy( BigInteger *bigint) {
    if( bigint) {
        if( bigint->data)
            free( bigint->data);
        free( bigint);
    }
}

void
big_integer_output( BigInteger *bigint) {
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
        result = big_integer_create( size, left->is_negative);
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
    if( big_integer_less( left, right)) {
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
        result = big_integer_create( size, true);
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
    result = big_integer_create( size, true);
    result->is_negative = left->is_negative != right->is_negative;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }
    BigInteger *temp= big_integer_create( size, false);
    _multiply( left, right, result, temp);
    big_integer_destroy( temp);
FINAL:
    if( is_temporary( left) && result != left)
        big_integer_destroy( left);
    if( is_temporary( right) && result != right)
        big_integer_destroy( right);
    return result;
}


BigInteger *
big_integer_divide( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    size_t size = left->size + right->size;
    result = big_integer_create( size, false);
    result->is_negative = left->is_negative != right->is_negative;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }else if( is_zero( right)) {
        result->is_nan = 1;
        goto FINAL;
    }
    if( _divide( left, right, result, NULL)) {
        big_integer_destroy( result);
        result = NULL;
    }
FINAL:
    if( is_temporary( left) && result != left)
        big_integer_destroy( left);
    if( is_temporary( right) && result != right)
        big_integer_destroy( right);
    return result;
}


BigInteger *
big_integer_mod( BigInteger *left, BigInteger *right) {
    BigInteger *result = NULL;
    if( left == NULL || right == NULL) goto FINAL;
    result = big_integer_create( right->size, false);
    result->is_negative = left->is_negative != right->is_negative;
    if( is_nan( left) || is_nan( right)) {
        result->is_nan = 1;
        goto FINAL;
    }else if( is_inf( left) || is_inf( right)) {
        result->is_inf = 1;
        goto FINAL;
    }else if( is_zero( right)) {
        result->is_nan = 1;
        goto FINAL;
    }
    if( _divide( left, right, NULL, result)) {
        big_integer_destroy( result);
        result = NULL;
    }
FINAL:
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
FINAL:
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
    if( is_nan( left) || is_nan( right) 
            || is_inf( left) || is_inf( right))
        result = false;
    if( is_zero( left) && is_zero( right))
        result = true;
    if( left->is_negative && !right->is_negative)
        result = true;
    if( !left->is_negative && right->is_negative)
        result = false;
    if( left->is_negative)
        result = !_abs_less( left, right);
    else
        result = !_abs_less( right, left);
FINAL:
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
FINAL:
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
FINAL:
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
FINAL:
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
FINAL:
    if( left && is_temporary( left))
        big_integer_destroy( left);
    if( right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}





