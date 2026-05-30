#ifndef CDATASTRUCTURES_DS_STATUS_CODE_H
#define CDATASTRUCTURES_DS_STATUS_CODE_H

#include <stdbool.h>

// Data structure status codes
typedef enum {
    DS_SUCCESS_OK = 0,
    DS_REMOVE_ERROR,
    DS_MEMORY_ERROR,
    DS_INDEX_ERROR,
    DS_EMPTY_ERROR,
    DS_NULL_ERROR,
    DS_ELEMENT_NOT_FOUND,
} ds_status_code_t;

// Data structure callback functions
typedef void (*print_callback)(const void* data);
typedef void (*clear_callback)(void* data);
typedef bool (*find_callback)(void* a, void* key);

#endif
