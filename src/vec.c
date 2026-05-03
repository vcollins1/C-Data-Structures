#include "vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Vec {
    size_t capacity;
    size_t size;
    size_t dataSize;
    void** dataArray;
};

struct VecIterator {
    size_t dataSize;
    size_t current;
    size_t last;
    void** data;
};

void resizeCapacity(vec_t* vec, size_t capacity) {
    if (vec->size == 0) capacity = 1;
    
    void** newDataArray = malloc(sizeof(*vec->dataArray) * capacity);
    if (newDataArray == NULL) return;

    memcpy(newDataArray, vec->dataArray, sizeof(*vec->dataArray) * vec->size);

    free(vec->dataArray);
    vec->dataArray = newDataArray;
    vec->capacity = capacity;
}

vec_t* createVec(size_t dataSize) {
    vec_t* vec = malloc(sizeof(vec_t));
    vec->capacity = 1;
    vec->size = 0;
    vec->dataSize = dataSize;
    vec->dataArray = malloc(sizeof(*vec->dataArray) * vec->capacity);

    return vec;
}

void destroyVec(vec_t* vec, clearCallback func) {
    clearVec(vec, func);
    free(vec->dataArray);
    free(vec);
}

VecStatusCode pushBack(vec_t* vec, void* data) {
    if (vec->size == vec->capacity) {
        resizeCapacity(vec, 2 * vec->capacity);
    }

    vec->dataArray[vec->size] = malloc(vec->dataSize);
    if (!vec->dataArray[vec->size]) return VecMemoryError;

    if (!vec->dataArray[vec->size])
        return VecMemoryError;

    memcpy(vec->dataArray[vec->size], data, vec->dataSize);
    ++vec->size;
    return VecOperationSuccess;
}

VecStatusCode insert(vec_t* vec, size_t index, void* data) {
    if (index > vec->size) return VecIndexError;
    if (vec->size == vec->capacity)
        resizeCapacity(vec, 2 * vec->capacity);

    vec->dataArray[vec->size] = malloc(vec->dataSize);
    if (!vec->dataArray[vec->size])
        return VecMemoryError;

    for (size_t i = vec->size; i > index; --i) {
        memcpy(vec->dataArray[i], vec->dataArray[i - 1], vec->dataSize);
    }
    
    memcpy(vec->dataArray[index], data, vec->dataSize);
    ++vec->size;
    return VecOperationSuccess;
}

VecStatusCode popBack(vec_t* vec, void *output) {
    if (vec->size == 0) return VecEmptyError;

    --vec->size;
    memcpy(output, vec->dataArray[vec->size], vec->dataSize);
    free(vec->dataArray[vec->size]);

    if (vec->size == vec->capacity/4)
        resizeCapacity(vec, vec->capacity/2);

    return VecOperationSuccess;
}

void clearVec(vec_t *vec, clearCallback func) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (func != NULL)
            func(vec->dataArray[i]);

        free(vec->dataArray[i]);
    }
    vec->size = 0;
}

size_t vecSize(vec_t* vec) {
    return vec->size;
}

size_t vecCapacity(vec_t* vec) {
    return vec->capacity;
}

vecIter_t* createVecIterator(vec_t* vec) {
    vecIter_t* iter = malloc(sizeof(vecIter_t));
    iter->dataSize = vec->dataSize;
    iter->current = 0;
    iter->last = vec->size;
    iter->data = vec->dataArray;

    return iter;
}

void destroyVecIterator(vecIter_t* iter) {
    free(iter);
}

void vecIteratorNext(vecIter_t* iter) {
    iter->current++;
}

void getVecIteratorData(vecIter_t* iter, void *output) {
    memcpy(output, iter->data[iter->current], iter->dataSize);
}

bool vecIterHasNext(vecIter_t* iter) {
    return iter->current < iter->last;
}

void printVec(vec_t* vec, printCallback func) {
    printf("[");
    char* sep = "";
    for (size_t i = 0; i < vec->size; ++i) {
        printf("%s", sep);
        func(vec->dataArray[i]);
        sep = ", ";
    }
    printf("]\n");
}
