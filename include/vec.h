#ifndef VEC_H
#define VEC_H
// Defines API for vector data structure
#include <stddef.h>
#include <stdbool.h>
#include "ds_utils.h"

typedef struct Vec vec_t;
typedef struct VecIter ds_vec_iter_t;

// Create/Destroy vec
vec_t* vec_create(size_t data_size);
void vec_destroy(vec_t* vec, clear_callback func);

// vec modifiers
ds_status_code_t vec_push_back(vec_t* vec, void* data);
ds_status_code_t vec_insert(vec_t* vec, size_t index, void* data);
ds_status_code_t vec_pop_back(vec_t* vec, void* output);
void vec_clear(vec_t* vec, clear_callback func);

// vec data access
size_t vec_size(vec_t* vec);
size_t vec_capacity(vec_t* vec);
ds_status_code_t vec_front(vec_t* vec, void* output);
ds_status_code_t vec_back(vec_t* vec, void* output);
ds_status_code_t vec_at(vec_t* vec, size_t index, void* output);

// vec iterator
ds_vec_iter_t* vec_create_iter(vec_t* vec);
void vec_destroy_iter(ds_vec_iter_t* iter);
void vec_iter_next(ds_vec_iter_t* iter);
void get_vec_iter_data(ds_vec_iter_t* iter, void* output);
bool vec_iter_has_next(ds_vec_iter_t* iter);

// vec display
void vec_print(vec_t* vec, print_callback func);

#endif
