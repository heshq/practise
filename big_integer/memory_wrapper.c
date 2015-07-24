#include <stdlib.h>
#include "memory_wrapper.h"

int malloc_failed = 0;;

void * __real_malloc( size_t size);

void * __wrap_malloc( size_t size)
{
    if( malloc_failed)
        return NULL;
    void *lptr = __real_malloc( size);
    return lptr;
}
