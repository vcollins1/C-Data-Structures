#ifndef VECTOR_H
#define VECTOR_H
// Defines API for vector data structure
#include <stddef.h>
#include <stdbool.h>
#include "ds_utils.h"

typedef struct Vector ds_vector_t;
typedef struct VectorIter ds_vector_iter_t;

// Create/Destroy vector
ds_vector_t* vector_create(size_t data_size);
void vector_destroy(ds_vector_t* vector, clear_callback func);

// add data to back of vector
ds_status_code_t vector_push_back(ds_vector_t* vector, void* data);

// add data at given index
ds_status_code_t vector_insert(ds_vector_t* vector, size_t index, void* data);

// remove data from the back of the vector
ds_status_code_t vector_pop_back(ds_vector_t* vector, clear_callback func);
void vector_clear(ds_vector_t* vector, clear_callback func);

// vector data access
size_t vector_size(ds_vector_t* vector);
size_t vector_capacity(ds_vector_t* vector);
bool vector_empty(ds_vector_t* vector);

// view data at the front of vector
ds_status_code_t vector_front(ds_vector_t* vector, void* output);

// view data at the back of vector
ds_status_code_t vector_back(ds_vector_t* vector, void* output);

// view of data at a given index
ds_status_code_t vector_at(ds_vector_t* vector, size_t index, void* output);

// vector iterator
ds_vector_iter_t* vector_create_iter(ds_vector_t* vector);
void vector_destroy_iter(ds_vector_iter_t* iter);
void vector_iter_next(ds_vector_iter_t* iter);
void get_vector_iter_data(ds_vector_iter_t* iter, void* output);
bool vector_iter_has_next(ds_vector_iter_t* iter);

// vector display
void vector_print(ds_vector_t* vector, print_callback func);

#endif
