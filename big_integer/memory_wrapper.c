#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "memory_wrapper.h"

#define PTR_NUM 8
#define ERROR 1

//save memory address allocated
typedef struct {
    void* value;
    int   released;
}node;
typedef struct {
    size_t size;
    size_t capacity;
    node** data;
}array_list;

static array_list* allocated = NULL;

int init_records() {
    if( allocated == NULL) {
        void* ptr = malloc( sizeof( array_list));
        if( ptr == NULL) {
            fprintf( stderr, "%s:%d:%s: malloc(): failed\n", __FILE__, __LINE__, __func__);
            return ERROR;
        }
        allocated = ptr;
        ptr = malloc( PTR_NUM * sizeof( void*));
        if( ptr == NULL) {
            fprintf( stderr, "%s:%d:%s: malloc(): failed\n", __FILE__, __LINE__, __func__);
            free( allocated);
            return ERROR;
        }
        allocated->data     = ptr;
        allocated->size     = 0;
        allocated->capacity = PTR_NUM;
    }
    return 0;
}

int resize_record() {
    size_t new_capacity = allocated->capacity << 1;
    void* new_ptr = realloc( allocated->data, new_capacity * sizeof( node));
    if( new_ptr == NULL) {
        fprintf( stderr, "%s:%d:%s: realloc(): failed\n", __FILE__, __LINE__, __func__);
        return ERROR;
    }
    allocated->data = new_ptr;
    allocated->capacity = new_capacity;
    return 0;
}

void free_record() {
    for( size_t idx = 0; idx < allocated->size; idx++)
        free( allocated->data[ idx]);
    if( allocated->data != NULL) {
        free( allocated->data);
        allocated->data = NULL;
    }
    if( allocated != NULL) {
        free( allocated);
        allocated = NULL;
    }
}

node* find_ptr_record( void* ptr) {
    for( size_t idx = 0 ; idx < allocated->size; idx ++)
        if( allocated->data[ idx]->value == ptr)
            return allocated->data[ idx];
    return NULL;
}

int record_ptr( void* ptr) {
    if( allocated->size >= allocated->capacity && resize_record())
        return ERROR;
    node* info= find_ptr_record( ptr);
    if( info ) {
        info->released = 0;
        return 0;
    }
    void* new_node = malloc( sizeof(node));
    if( new_node == NULL)
        return ERROR;
    allocated->data[ allocated->size] = new_node;
    allocated->data[ allocated->size]->value    = ptr;
    allocated->data[ allocated->size]->released = 0;
    allocated->size++;
    return 0;
}

void* my_malloc( size_t size) {
    if( malloc_failed)
        return NULL;
    void* new_ptr = malloc( size);
    if( new_ptr && record_ptr( new_ptr))
        free( new_ptr);
    return new_ptr;
}

void* my_realloc( void* ptr, size_t size) {
    if( malloc_failed)
        return NULL;
    if( ptr == NULL)
        return NULL;
    node* info= find_ptr_record( ptr);
    if( info) {
        void* new_ptr = realloc( ptr, size);
        if( new_ptr != NULL)
            info->value = new_ptr;
        return new_ptr; 
    } else {
        //realloc_ptr_not_exist ++;
        return NULL;
    }
}

void my_free( void* ptr) {
    if( ptr == NULL) {
        fprintf( stderr, "%s:%d:%s: released ptr more than once ptr\n", __FILE__, __LINE__, __func__);
        return;
    }
    node* info= find_ptr_record( ptr);
    if( info) {
        free( ptr);
        info->released++;
    } else {
        //realloc_ptr_not_exist++;
        free( ptr);
    }
}

void memory_report() {
    int pass = 0;
    /**if(realloc_ptr_not_exist){
        puts( "wild pointer");
        pass++;
    }*/
    for( size_t idx = 0; idx < allocated->size; idx ++) {
        if( allocated->data[ idx]->released == 0)
            puts( "pointer not released");
        if( allocated->data[ idx]->released > 1)
            puts( "repeat released pointer");
        if( allocated->data[ idx]->released != 1)
            pass++;
    }
    if( !pass)
        puts("memery test pass");
}

