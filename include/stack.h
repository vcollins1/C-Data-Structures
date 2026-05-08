#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"
#include "vector.h"

typedef ds_vector_t ds_stack_t;

ds_stack_t* stack_create(size_t data_size);
void stack_destroy(ds_stack_t* stack, clear_callback func);

// add data to trhe stack
ds_status_code_t stack_push(ds_stack_t* stack, void* data);

// remove data from the stack
ds_status_code_t stack_pop(ds_stack_t* stack, clear_callback func);

// view data at the top of the stack without removal
ds_status_code_t stack_top(ds_stack_t* stack, void* output);

size_t stack_size(ds_stack_t* stack);
bool stack_empty(ds_stack_t* stack);

#endif
