#ifndef CDATASTRUCTURES_DEQUE_H
#define CDATASTRUCTURES_DEQUE_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"
#include "list.h"

typedef ds_list_t ds_deque_t;

ds_deque_t* deque_create(size_t data_size);
void deque_destroy(ds_deque_t* deque, clear_callback func);

size_t deque_size(ds_deque_t* deque);
bool deque_empty(ds_deque_t* deque);

ds_status_code_t deque_front(ds_deque_t* deque, void* output);
ds_status_code_t deque_back(ds_deque_t* deque, void* output);

ds_status_code_t deque_push_front(ds_deque_t* deque, void* data);
ds_status_code_t deque_push_back(ds_deque_t* deque, void* data);
ds_status_code_t deque_pop_front(ds_deque_t* deque, clear_callback func);
ds_status_code_t deque_pop_back(ds_deque_t* deque, clear_callback func);

#endif
