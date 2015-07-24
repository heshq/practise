#include <errno.h>
#include <limits.h>//CHAR_BIT
#include <stdio.h>
#include <stdlib.h>//malloc,realloc,free
#include <string.h>//memset,memcpy
#include "big_integer.h"

#define YES 1
#define NO 0
#define success 0
#define failed 1

#define GOTO_IF_ALLOC_ERROR( lable) if( errno) { goto lable; }

//inner function
BigInteger*
_create_big_integer( const unsigned *value, SYMBOL symbol, unsigned size , int is_temporary )
{
    if( size <= 0 ) return NULL;
    BigInteger *bigint = malloc( sizeof( BigInteger));
    if( bigint == NULL) return NULL;
    bigint->data = malloc( size * sizeof( unsigned));
    if( bigint->data == NULL) {
        free( bigint);
        return NULL;
    }
    bigint->is_negative  = symbol;
    bigint->is_temporary = is_temporary ? 1 : 0;
    bigint->is_nan       = 0;
    bigint->is_inf       = 0;
    bigint->size         = size;
    if( value != NULL)
        memcpy( bigint->data, value, size * sizeof( unsigned));
    else
        memset( bigint->data, 0, size);
    return bigint;
}

/*
 * compare only absolute value
 * left and right must not 0, and must not 0 in upper
 */
int
_array_less_abs( unsigned *left, size_t left_size, unsigned *right, size_t right_size)
{
    size_t none_zero_left = left_size - 1, none_zero_right = right_size - 1;
    while( none_zero_left > 0 && left[ none_zero_left] == 0)
        none_zero_left --;
    while( none_zero_right > 0 && right[ none_zero_right] == 0)
        none_zero_right --;
    if( none_zero_left != none_zero_right)
        return none_zero_left < none_zero_right;
    else
        return left[ none_zero_left] < right[ none_zero_right];
}

int
_relloc_data( BigInteger *bigint, int new_size)
{
    if( new_size == bigint->size)
        return success;
    unsigned *ptr = ( unsigned *)realloc( bigint->data, new_size * sizeof( unsigned));
    if( ptr )
        bigint->data = ptr;
    else
        return failed;
    bigint->size = new_size;
    return success;
}

//bigInt must not equal 0,size must not equal NULL
int
_resize_to_fit_data( unsigned *data, size_t size)
{
    size_t idx = size - 1;
    while( ! data[ idx])
        idx--;
    if( idx < size - 1) {
        realloc( data, ( idx + 1) * sizeof( unsigned));
        size = idx + 1;
    }
    return size;
}

int
_is_zero( BigInteger * bigint)
{
    for ( int i = 0; i < bigint->size; i++)
        if( bigint->data[ i] != 0)
            return NO;
    return YES;
}

//interface function
int
is_nan( BigInteger *bigint)
{
    if( bigint == NULL) return NO;
    return  bigint->is_nan;
}

int
is_inf( BigInteger *bigint)
{
    if( bigint == NULL) return NO;
    return  bigint->is_inf;
}

int
is_temporary( BigInteger *bigint)
{
    if( bigint == NULL) return NO;
    return  bigint->is_temporary;
}

int
is_normal( BigInteger *bigint)
{
    return !is_nan( bigint) && !is_inf( bigint);
}

int
is_negative( BigInteger *bigint)
{
    return bigint->is_negative;
}

int
big_integer_assign( BigInteger *target, BigInteger *source )
{
    if( target == source ) return success;
    int result = success;
    if( source->size > target->size)
        if( _relloc_data( target, source->size)) {
            result = failed;
            goto FINAL;
        }
    target->is_negative = source->is_negative;
    target->is_nan      = source->is_nan;
    target->is_inf      = source->is_inf;
    memset( target->data, 0 , target->size * sizeof( unsigned));
    memcpy( target->data, source->data, target->size * sizeof( unsigned));
FINAL:
    if( is_temporary( source))
        big_integer_destroy( source);
    return result;
}

BigInteger*
big_integer_create( const unsigned *value, SYMBOL symbol, unsigned size )
{
    return _create_big_integer( value, symbol, size, PERSISTENT_OBJ);
}

void
big_integer_destroy( BigInteger *bigint )
{
    if( bigint) {
        if( bigint->data ) {
            free( bigint->data);
            bigint->data = NULL;
        }
        free( bigint);
        bigint = NULL;
    }
}

int
_is_array_zero( unsigned *array, size_t size)
{
    for( size_t idx = 0; idx < size; idx++) {
        if( array[ idx])
            return NO;
    }
    return YES;
}

#define SPLICE ( CHAR_BIT * sizeof( unsigned) >> 1)
#define MASK ( ( 1 << SPLICE) - 1 )
void
_big_integer_multiply( BigInteger *left, BigInteger *right, BigInteger *result) {
    int size = left->size + right->size;
    BigInteger *temp = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, size, PERSISTENT_OBJ);
    GOTO_IF_ALLOC_ERROR( FINAL);
    //calculate
    memset( result->data, 0, result->size * sizeof( unsigned));
    for( size_t i = 0; i < left->size; i ++) {
        for( size_t j = 0; j < right->size; j ++) {
            //use karatsuba algorithm
            unsigned x0 = left->data[ i] &  MASK;
            unsigned x1 = left->data[ i] >> SPLICE;
            unsigned y0 = right->data[ j] &  MASK;
            unsigned y1 = right->data[ j] >> SPLICE;
            unsigned z0 = x0 * y0;
            unsigned z1 = x1 * y1;
            unsigned z2 = ( x1 + x0) * ( y1 + y0) - z0 - z1;
            unsigned z3 = z2 >> SPLICE;
            z2 = z2 << SPLICE;
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            temp->data[ i + j] = z0;
            big_integer_assign( result, big_integer_add( result, temp));
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            temp->data[ i + j] = z2;
            big_integer_assign( result, big_integer_add( result, temp));
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            temp->data[ i + j + 1] = z1;
            big_integer_assign( result, big_integer_add( result, temp));
            memset( temp->data, 0, temp->size * sizeof( unsigned));
            temp->data[ i + j + 1] = z3;
            big_integer_assign( result, big_integer_add( result, temp));
        }
    }
    big_integer_destroy( temp);
FINAL:
    return;
}

void
_big_integer_divide( BigInteger *left, BigInteger *right, BigInteger *quotient, BigInteger *remainder) {
    BigInteger *product = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, left->size, TEMPORARY_OBJ);
    BigInteger *temp    = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, 1, PERSISTENT_OBJ);
    memcpy( remainder->data, left->data, left->size*sizeof( unsigned));
    unsigned *original_data = remainder->data;
    size_t original_size = remainder->size;
    for( int remain = left->size - right->size; remain >= 0; remain --) {
        remainder->data = original_data + remain;
        remainder->size = original_size - remain;
        if( _array_less_abs( remainder->data, remainder->size, right->data, right->size)) {
            quotient->data[ remain] = 0;
            continue;
        }
        unsigned lower = 0, upper = ~0u, middle = 0;
        do{
            middle = ( lower >> 1) + ( upper >> 1) + ( lower & upper & 0x1);
            temp->data[ 0] = middle;
            _big_integer_multiply( right, temp, product);
            if( _array_less_abs( remainder->data, remainder->size, product->data, product->size)) {
                upper = middle;
                continue;
            }
            BigInteger *result = big_integer_minus( remainder, product);
            if( !_array_less_abs( result->data ,result->size, right->data, right->size)) {
                lower = middle;
                continue;
            }
            big_integer_assign( remainder, result);
            break;
        }while( lower < upper -1 );
        quotient->data[ remain] = middle;
    }
}

#undef SPLICE
#undef MASK

void
big_integer_output( BigInteger *bigint)
{
    if( bigint == NULL || bigint->data == NULL) return;
    if( is_inf( bigint)) {
        puts( "inf\n");
    } else if( is_nan( bigint)) {
        puts( "nan\n");
    } else{
        if( bigint->is_negative)
            printf("%s","-");
        BigInteger *divisor = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, 1, PERSISTENT_OBJ);
        divisor->data[ 0] = 10;
        BigInteger *dividend = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, bigint->size, PERSISTENT_OBJ);
        big_integer_assign(dividend,  bigint);
        BigInteger *quotient  = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, bigint->size, PERSISTENT_OBJ);
        BigInteger *remainder = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, bigint->size, PERSISTENT_OBJ);
        while( !_is_array_zero( dividend->data, dividend->size)
              && !_array_less_abs( dividend->data, dividend->size, divisor->data, divisor->size)) {
            memset( remainder->data, 0, remainder->size * sizeof( unsigned));
            memset( quotient->data,  0,  quotient->size * sizeof( unsigned));
            _big_integer_divide( dividend, divisor, quotient, remainder);
            big_integer_assign( dividend, quotient);
            printf( "%u", remainder->data[ 0]);
        }
        printf( "%u\n", dividend->data[ 0]);
        free( remainder);
        free( divisor);
        free( dividend);
        free( quotient);
    }
    if( is_temporary( bigint))
        big_integer_destroy( bigint);
}

//TODO
int
big_integer_input( BigInteger *bigint)
{
    puts( " plz enter is negative, o : positive number other: negative number");
    return success;
}

BigInteger*
big_integer_add( BigInteger *left, BigInteger *right )
{
    if( left == NULL || right == NULL || left->data == NULL || right->data == NULL) goto FINAL;
    BigInteger *result = NULL;
    //choose result object
    if( is_temporary( left)) {
        result = left;
        if( left->size < right->size)
            _relloc_data( left, right->size);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }else if( is_temporary( right)) {
        result = right;
        if( right->size < left->size)
            _relloc_data( right, left->size);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }else {
        int size = left->size > right->size ? left->size : right->size;
        SYMBOL symbol = left->is_negative? NEGATIVE_NUMBER: POSITIVE_NUMBER;
        result = _create_big_integer( EMPTY_NUMBER, symbol, size, TEMPORARY_OBJ);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }
    
    if( is_nan( left) || is_nan( right)
       || ( is_inf( left) && is_inf( right) && ( left->is_negative != right->is_negative)) ){
        result->is_inf = NO;
        result->is_nan = YES;
        goto FINAL;
    }else if(  is_inf( right) || is_inf( left)) {
        result->is_inf = YES;
        goto FINAL;
    }
    
    if( left->is_negative != right->is_negative) {
        right->is_negative = !right->is_negative;
        return big_integer_minus( left, right);
    }
    
    //calculate
    int carry_bit = 0;
    int next_carry_bit = 0;
    size_t index = 0;
    for( ; index < left->size && index < right->size; index ++) {
        next_carry_bit = ( ( ( left->data[ index] & 0x1) & ( right->data[ index] & 0x1)) +
                          ( left->data[ index] >> 1) + ( right->data[ index] >> 1)) >> ( CHAR_BIT * sizeof( unsigned) - 2);
        result->data[ index] = left->data[ index] + right->data[ index] + carry_bit;
        carry_bit = next_carry_bit;
    }
    while( carry_bit & ( index < result->size)) {
        next_carry_bit = result->data[ index] == ~0u? 1 : 0;
        result->data[ index] += carry_bit;
        carry_bit = next_carry_bit;
        index++;
    }
    
FINAL:
    if( result != left && is_temporary( left))
        big_integer_destroy( left);
    if( result != right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}

BigInteger*
big_integer_minus( BigInteger *left, BigInteger *right )
{
    if( left == NULL || right == NULL || left->data == NULL || right->data == NULL) goto FINAL;
    BigInteger *result = NULL;
    //choose result object
    if( is_temporary( left)) {
        result = left;
        if( left->size < right->size)
            _relloc_data( left, right->size);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }else if( is_temporary( right)) {
        result = right;
        if( right->size < left->size)
            _relloc_data( right, left->size);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }else {
        int size = left->size > right->size ? left->size : right->size;
        SYMBOL symbol = left->is_negative? NEGATIVE_NUMBER: POSITIVE_NUMBER;
        result = _create_big_integer( EMPTY_NUMBER, symbol, size, TEMPORARY_OBJ);
        GOTO_IF_ALLOC_ERROR( FINAL);
    }
    
    if( is_nan( left) || is_nan( right)
       || ( is_inf( left) && is_inf( right) && ( left->is_negative != right->is_negative)) ){
        result->is_inf = NO;
        result->is_nan = YES;
        goto FINAL;
    }else if(  is_inf( right) || is_inf( left)) {
        result->is_inf = YES;
        goto FINAL;
    }
    //calculate
    size_t index = 0;
    int borrow_bit = 0;
    for( ; index < left->size && index < right->size; index ++) {
        if( left->data[ index] < right->data[ index] + borrow_bit) {
            unsigned result_num = left->data[ index] - right->data[ index] - borrow_bit;
            result->data[ index] = ~result_num + 1;
            borrow_bit = 1;
        } else {
            result->data[ index] = left->data[ index] - right->data[ index] - borrow_bit;
            borrow_bit = 0;
        }
    }
    while( borrow_bit && index < left->size) {
        int next_carry_bit = ( left->data[ index] == 0);
        result->data[ index] = left->data[ index] - borrow_bit;
        borrow_bit = next_carry_bit;
        index++;
    }
    
FINAL:
    if( result != left && is_temporary( left))
        big_integer_destroy( left);
    if( result != right && is_temporary( right))
        big_integer_destroy( right);
    return result;
}

BigInteger*
big_integer_multiply( BigInteger *left, BigInteger *right )
{
    if( left == NULL || right == NULL || left->data == NULL || right->data == NULL) goto FINAL;
    BigInteger *result = NULL;
    if( is_nan( left) || ( is_inf( left) && is_normal( right))) {
        result = left;
        goto FINAL;
    }else if(  is_nan( right) || _is_zero( left)
             || ( is_inf( right) && is_normal( left))) {
        result = right;
        goto FINAL;
    }
    //choose result object
    int size = left->size + right->size;
    SYMBOL symbol = left->is_negative != right->is_negative ? NEGATIVE_NUMBER: POSITIVE_NUMBER;
    result = _create_big_integer( EMPTY_NUMBER, symbol, size, TEMPORARY_OBJ);
    _big_integer_multiply( left, right, result);
FINAL:
    if( is_temporary( left))
        big_integer_destroy( left);
    if( is_temporary( right))
        big_integer_destroy( right);
    return result;
}

BigInteger*
big_integer_divide( BigInteger *left, BigInteger *right )
{
    if( left == NULL || right == NULL || left->data == NULL || right->data == NULL) goto FINAL;
    BigInteger *result = NULL;
    if( is_inf( left) && is_inf( right)) {
        left->is_inf = NO;
        left->is_nan = YES;
        result = left;
        goto FINAL;
    } else if( is_nan( left) || _is_zero( right)
              || ( is_inf( left) && is_normal( right))) {
        result = left;
        goto FINAL;
    }else if(  is_nan( right) || _is_zero( left)
             || ( is_inf( right) && is_normal( left))) {
        result = right;
        goto FINAL;
    }
    //calculate
    BigInteger *quotient  = _create_big_integer( EMPTY_NUMBER, left->is_negative, left->size, PERSISTENT_OBJ);
    BigInteger *remainder = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, left->size, PERSISTENT_OBJ);
    _big_integer_divide( left, right, quotient, remainder);
    free( remainder);
FINAL:
    if( is_temporary( left))
        big_integer_destroy( left);
    if( is_temporary( right))
        big_integer_destroy( right);
    return quotient;
}

BigInteger*
big_integer_mod( BigInteger *left, BigInteger *right )
{
    if( left == NULL || right == NULL || left->data == NULL || right->data == NULL) goto FINAL;
    BigInteger *result = NULL;
    if( is_inf( left) && is_inf( right)) {
        left->is_inf = NO;
        left->is_nan = YES;
        result = left;
        goto FINAL;
    } else if( is_nan( left) || _is_zero( right)
              || ( is_inf( left) && is_normal( right))) {
        result = left;
        goto FINAL;
    }else if(  is_nan( right) || _is_zero( left)
             || ( is_inf( right) && is_normal( left))) {
        result = right;
        goto FINAL;
    }
    //calculate
    BigInteger *quotient  = _create_big_integer( EMPTY_NUMBER, left->is_negative, left->size, PERSISTENT_OBJ);
    BigInteger *remainder = _create_big_integer( EMPTY_NUMBER, POSITIVE_NUMBER, right->size, PERSISTENT_OBJ);
    _big_integer_divide( left, right, quotient, remainder);
    free( quotient);
FINAL:
    if( is_temporary( left))
        big_integer_destroy( left);
    if( is_temporary( right))
        big_integer_destroy( right);
    return remainder;
}

int
big_integer_less( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return NO;
    if( is_negative( left) && !is_negative( right))
        return YES;
    if( !is_negative( left) && is_negative( right))
        return NO;
    if( is_negative( left))
        return _array_less_abs( right->data, right->size, left->data, left->size);
    else
        return _array_less_abs( left->data, left->size, right->data, right->size);
}

int
big_integer_less_equal( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return YES;
    if( is_negative( left) && !is_negative( right))
        return YES;
    if( !is_negative( left) && is_negative( right))
        return NO;
    if( is_negative( left))
        return !_array_less_abs( left->data, left->size, right->data, right->size);
    else
        return !_array_less_abs( right->data, right->size, left->data, left->size);
}

int
big_integer_greater( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return NO;
    if( is_negative( left) && !is_negative( right))
        return NO;
    if( !is_negative( left) && is_negative( right))
        return YES;
    if( is_negative( left))
        return _array_less_abs( left->data, left->size, right->data, right->size);
    else
        return _array_less_abs( right->data, right->size, left->data, left->size);
}

int
big_integer_greater_equal( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return YES;
    if( is_negative( left) && !is_negative( right))
        return NO;
    if( !is_negative( left) && is_negative( right))
        return YES;
    if( is_negative( left))
        return !_array_less_abs( right->data, right->size, left->data, left->size);
    else
        return !_array_less_abs( left->data, left->size, right->data, right->size);
}

int
big_integer_equal( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return YES;
    if( left->is_negative != right->is_negative)
        return NO;
    return !_array_less_abs( left->data, left->size, right->data, right->size)
    && !_array_less_abs( right->data, right->size, left->data, left->size);
}

int
big_integer_not_equal( BigInteger *left, BigInteger *right )
{
    if( is_nan( left) || is_inf( left) || is_nan( right) || is_inf( right))
        return NO;
    if( _is_zero( left) && _is_zero( right))
        return NO;
    if( left->is_negative != right->is_negative)
        return YES;
    return _array_less_abs( left->data, left->size, right->data, right->size)
    || _array_less_abs( right->data, right->size, left->data, left->size);
}