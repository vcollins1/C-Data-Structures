#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>
#include "ds_utils.h"

// List data types
typedef struct List ds_list_t;
typedef struct ListIter ds_list_iter_t;

// Create and Destory List functions
ds_list_t* list_create(size_t data_size);
void list_destroy(ds_list_t* list, clear_callback func);

// Add elements to list
ds_status_code_t list_unshift(ds_list_t* list, void* data);
ds_status_code_t list_add_back(ds_list_t* list, void* data);
ds_status_code_t list_insert_at(ds_list_t* list, size_t index, void* data);

// Remove elements from the list
ds_status_code_t list_shift(ds_list_t* list, void* output);
ds_status_code_t list_remove_back(ds_list_t* list, void* output);
ds_status_code_t list_remove_at(ds_list_t* list, size_t index, void* output);

// Utility functions
void list_clear(ds_list_t* list, clear_callback func);
size_t list_size(ds_list_t* list);
bool is_list_empty(ds_list_t* list);
ds_status_code_t list_find(ds_list_t* list, void* key, void* found, find_callback func);
ds_status_code_t list_set(ds_list_t* list, size_t index, void* update);

// List iteratoion
ds_list_iter_t* list_create_iter(ds_list_t* list);
void list_destroy_iter(ds_list_iter_t* iter);
void list_iter_next(ds_list_iter_t* iter);
void get_list_iter_data(ds_list_iter_t* iter, void* output);
bool list_iter_has_next(ds_list_iter_t* iter);

// Display elements of list
void list_print(ds_list_t* list, print_callback func);

#endif
