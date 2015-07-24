#ifndef BIG_INTEGER_H
#define BIG_INTEGER_H

typedef struct {
    unsigned is_negative:1;//indicate if the number is negative 1:negative
    unsigned is_temporary:1;//indicate if the struct is temporary object 1:temporary
    unsigned is_nan:1;//indicate if the struct is not a number 1:nan
    unsigned is_inf:1;//indicate if the struct is infinity number 1:inf
    unsigned size;//the size of number
    unsigned *data;
} BigInteger;

typedef enum
{
    POSITIVE_NUMBER,
    NEGATIVE_NUMBER
} SYMBOL;

#define EMPTY_NUMBER NULL
typedef enum
{
    PERSISTENT_OBJ,
    TEMPORARY_OBJ
}OBJ_TYPE;

//#define ALLOC_ERROR 1

/**
 * return NOT ZERO number only when it is not NULL and is not a number
 */
int is_nan( BigInteger *bigint);

/**
 * return NOT ZERO number only when it is not NULL and is infinity number
 */
int is_inf( BigInteger *bigint);

/**
 * return NOT ZERO number only when it is not NULL and is temporary object
 */
int is_temporary( BigInteger *bigint);
//int is_finite( BigInteger *bigint[]);

/**
 * return NOT ZERO number only when it is not NULL ,not infinity number and is a number
 */
int is_normal( BigInteger *bigint);

/**
 * 1. assign source object to target object, and will
 *    free source object if it is temporary object.
 * 2. DO NOT assign source to target directly( like target = source).
 *    It may cause memory leak.
 * 3. return 0 if allocate memory for target failed,other will return 1.
 */
int big_integer_assign( BigInteger *target, BigInteger *source );

/**
 * 1 create none-temporary object with size, symbol and value specified.
 * 2 if number is negative ,DO NOT give two's complement ,give it like "-1" in decimal form.
 * 3 return NULL if allocate memory failed.
 */
BigInteger* big_integer_create( const unsigned *value, SYMBOL symbol, unsigned size );

/**
 * 1 free BigInteger object.
 * 2 user must call this function to free any none-temporary object.
 */
void big_integer_destroy( BigInteger* bigint );

/**
 * output bigint to console in decimal form.
 */
void big_integer_output( BigInteger* bigint);

/**
 * get bigint data from console in decimal form.
 * return 0 if allocate memory failed.
 */
int big_integer_input( BigInteger* bigint);

/**
 * 1. return a temporary object which data is BigInteger left add BigInteger right .
 * 2. DO NOT assign the result to a variable directly, use
 *   function big_integer_assign instead.
 * 3. free any of parameters if it is temporary object.
 */
BigInteger* big_integer_add( BigInteger *left, BigInteger *right );

/**
 * 1. return a temporary object which data is BigInteger left minus BigInteger right .
 * 2. DO NOT assign the result to a variable directly, use
 * function big_integer_assign instead.
 * 3. free any of parameters if it is temporary object.
 * 4. return NULL and set errno if allocate memory failed.
 * 5. return inf if one of param is inf .
 * 6. return nan if one of param is nan, NO MATTER what another parameter is.
 */
BigInteger* big_integer_minus( BigInteger *left, BigInteger *right );

/**
 * 1. return a temporary object which data is BigInteger left divide BigInteger right .
 * 2. DO NOT assign the result to a variable directly, use
 *  function big_integer_assign instead.
 * 3. free any of parameters if it is temporary object.
 * 4. return NULL and set errno if allocate memory failed.
 * 5. return inf if one of param is inf .
 * 6. return nan if one of param is nan, NO MATTER what another parameter is.
 */
BigInteger* big_integer_multiply( BigInteger *left, BigInteger *right);

/**
 * 1. return a temporary object which data is BigInteger left divide BigInteger right .
 * 2. DO NOT assign the result to a variable directly, use
 *   function big_integer_assign instead.
 * 3. set errno when there is exception.
 * 4. free any of parameters if it is temporary object.
 * 5. return inf if one of param is inf .
 * 6. return nan if one of param is nan, NO MATTER what another parameter is.
 */
BigInteger* big_integer_divide( BigInteger *left, BigInteger *right );

/**
 * 1. return a temporary object which data is BigInteger left mod BigInteger right.
 * 2. DO NOT assign the result to a variable directly, use
 *   function big_integer_assign instead.
 * 3. set errno when there is exception.
 * 4. free any of parameters if it is temporary object.
 * 6. return inf if one of param is inf .
 * 6. return nan if one of param is nan, NO MATTER what another parameter is.
 */
BigInteger* big_integer_mod( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left less than BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_less( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left less than BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_less_equal( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left greater than BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_greater( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left greater or equal than BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_greater_equal( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left equal BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_equal( BigInteger *left, BigInteger *right );

/**
 * 1. return nonzero number if BigInteger named left not equal BigInteger right, else return 0.
 * 2. free object if any of parameters is temporary object.
 * 3. return false if one of param is nan or inf.
 */
int big_integer_not_equal( BigInteger *left, BigInteger *right );

#endif