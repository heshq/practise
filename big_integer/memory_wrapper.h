#ifndef MEMORY_WRAPPER_H
#define MEMORY_WRAPPER_H

/**
 * malloc will always return NULL if malloc_failed is not 0
 */
extern int malloc_failed;

void* my_malloc( size_t);

void* my_realloc( void*, size_t);

void  my_free( void*);

int init_records();

void free_record();

void memory_report();

#endif


