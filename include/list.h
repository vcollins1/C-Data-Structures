#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdbool.h>

// List data types
typedef struct List list_t;
typedef struct ListIter listIter_t;

// List callback functions types
typedef void (*print_callback)(const void* data);
typedef void (*clear_callback)(void* data);
typedef bool (*find_callback)(void* a, void* key);

// List status and error codes
typedef enum {
    LIST_SUCCESS_OK = 0,
    LIST_REMOVE_ERROR,
    LIST_MEMORY_ERROR,
    LIST_INDEX_ERROR,
    LIST_EMPTY_ERROR,
    LIST_ELEMENT_NOT_FOUND,
} ListStatusCode_t;

// Create and Destory List functions
list_t* list_create(size_t dataSize);
void list_destroy(list_t* list, clear_callback func);

// Add elements to list
ListStatusCode_t list_unshift(list_t* list, void* data);
ListStatusCode_t list_add_back(list_t* list, void* data);
ListStatusCode_t list_insert_at(list_t* list, size_t index, void* data);

// Remove elements from the list
ListStatusCode_t list_shift(list_t* list, void* output);
ListStatusCode_t list_remove_back(list_t* list, void* output);
ListStatusCode_t list_remove_at(list_t* list, size_t index, void* output);

// Utility functions
void list_clear(list_t* list, clear_callback func);
size_t list_size(list_t* list);
bool is_list_empty(list_t* list);
ListStatusCode_t list_find(list_t* list, void* key, void* found, find_callback func);
ListStatusCode_t list_set(list_t* list, size_t index, void* update);

// List iteratoion
listIter_t* list_create_iter(list_t* list);
void list_destroy_iter(listIter_t* iter);
void list_iter_next(listIter_t* iter);
void get_list_iter_data(listIter_t* iter, void* output);
bool list_iter_has_next(listIter_t* iter);

// Display elements of list
void list_print(list_t* list, print_callback func);

#endif
