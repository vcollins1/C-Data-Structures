#ifndef DS_STATUS_CODE_H
#define DS_STATUS_CODE_H

typedef enum {
    DS_SUCCESS_OK = 0,
    DS_REMOVE_ERROR,
    DS_MEMORY_ERROR,
    DS_INDEX_ERROR,
    DS_EMPTY_ERROR,
    DS_ELEMENT_NOT_FOUND,
} DS_StatusCode_t;

#endif
