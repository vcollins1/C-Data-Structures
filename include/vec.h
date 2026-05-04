#ifndef VEC_H
#define VEC_H
// Defines API for vector data structure
#include <stddef.h>
#include <stdbool.h>
#include "ds_status_code.h"

typedef struct Vec vec_t;
typedef struct VecIter vecIter_t;

typedef void (*print_callback)(const void* data);
typedef void (*clear_callback)(void* data);

// Create/Destroy vec_t
vec_t* vec_create(size_t data_size);
void vec_destroy(vec_t* vec, clear_callback func);

// vec_t modifiers
DS_StatusCode_t vec_push_back(vec_t* vec, void* data);
DS_StatusCode_t vec_insert(vec_t* vec, size_t index, void* data);
DS_StatusCode_t vec_pop_back(vec_t* vec, void* output);
void vec_clear(vec_t* vec, clear_callback func);

// vec_t data access
size_t vec_size(vec_t* vec);
size_t vec_capacity(vec_t* vec);
DS_StatusCode_t vec_front(vec_t* vec, void* output);
DS_StatusCode_t vec_back(vec_t* vec, void* output);
DS_StatusCode_t vec_at(vec_t* vec, size_t index, void* output);

// vec_t iterator
vecIter_t* vec_create_iter(vec_t* vec);
void vec_destroy_iter(vecIter_t* iter);
void vec_iter_next(vecIter_t* iter);
void get_vec_iter_data(vecIter_t* iter, void* output);
bool vec_iter_has_next(vecIter_t* iter);

// Display vec_t
void vec_print(vec_t* vec, print_callback func);

#endif
