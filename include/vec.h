#ifndef VEC_H
#define VEC_H
// Defines API for vector data structure
#include <stddef.h>
#include <stdbool.h>

typedef enum {
    VecOperationSuccess = 0,
    VecRemoveError,
    VecMemoryError,
    VecIndexError,
    VecEmptyError,
    VecNotFoundError,
} VecStatusCode;

typedef struct Vec vec_t;
typedef struct VecIterator vecIter_t;

typedef void (*printCallback)(const void* data);
typedef void (*clearCallback)(void* data);

// Create/Destroy vec_t
vec_t* createVec(size_t dataSize);
void destroyVec(vec_t* vec, clearCallback func);

// vec_t modifiers
VecStatusCode pushBack(vec_t* vec, void* data);
VecStatusCode insert(vec_t* vec, size_t index, void* data);
VecStatusCode popBack(vec_t* vec, void* output);
void clearVec(vec_t* vec, clearCallback func);

// vec_t data access
size_t vecSize(vec_t* vec);
size_t vecCapacity(vec_t* vec);
VecStatusCode front(vec_t* vec, void* output);
VecStatusCode back(vec_t* vec, void* output);
VecStatusCode at(vec_t* vec, size_t index, void* output);

// vec_t iterator
vecIter_t* createVecIterator(vec_t* vec);
void destroyVecIterator(vecIter_t* iter);
void vecIteratorNext(vecIter_t* iter);
void getVecIteratorData(vecIter_t* iter, void* output);
bool vecIterHasNext(vecIter_t* iter);

// Display vec_t
void printVec(vec_t* vec, printCallback func);

#endif
