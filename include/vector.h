#ifndef VEC_H
#define VEC_H
// Defines API for vector data structure
#include <stddef.h>
#include <stdbool.h>
#include "ds_utils.h"

typedef struct Vector ds_vector_t;
typedef struct VectorIter ds_vector_iter_t;

// Create/Destroy vec
ds_vector_t* vector_create(size_t data_size);
void vector_destroy(ds_vector_t* vec, clear_callback func);

// add data to to back of vec
ds_status_code_t vector_push_back(ds_vector_t* vec, void* data);

// add data at given index
ds_status_code_t vector_insert(ds_vector_t* vec, size_t index, void* data);

// remove data from the bac of the vec
ds_status_code_t vector_pop_back(ds_vector_t* vec, clear_callback func);
void vec_clear(ds_vector_t* vec, clear_callback func);

// vec data access
size_t vector_size(ds_vector_t* vec);
size_t vector_capacity(ds_vector_t* vec);
bool vector_empty(ds_vector_t* vec);

// view of data at the front of vec
ds_status_code_t vector_front(ds_vector_t* vec, void* output);

// view of data at the back of vec
ds_status_code_t vector_back(ds_vector_t* vec, void* output);

// view of data at a given index
ds_status_code_t vector_at(ds_vector_t* vec, size_t index, void* output);

// vec iterator
ds_vector_iter_t* vector_create_iter(ds_vector_t* vec);
void vector_destroy_iter(ds_vector_iter_t* iter);
void vector_iter_next(ds_vector_iter_t* iter);
void get_vector_iter_data(ds_vector_iter_t* iter, void* output);
bool vector_iter_has_next(ds_vector_iter_t* iter);

// vec display
void vector_print(ds_vector_t* vec, print_callback func);

#endif
