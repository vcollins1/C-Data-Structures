#ifndef VEC_H
#define VEC_H
// Defines API for vector data structure
#include <stddef.h>

typedef enum {
    VecOperationSuccess = 0,
    VecRemoveError,
    VecMemoryError,
    VecIndexError,
    VecEmptyError,
    VecNotFoundError,
} VecStatusCode;

typedef struct Vec vec_t;

typedef void (*printCallback)(const void* data);
typedef void (*clearCallback)(void* data);

vec_t* createVec(size_t dataSize);
void destroyVec(vec_t* vec, clearCallback func);

VecStatusCode pushBack(vec_t* vec, void* data);
VecStatusCode insert(vec_t* vec, size_t index, void* data);

void clearVec(vec_t* vec, clearCallback func);

void printVec(vec_t* vec, printCallback func);

#endif
