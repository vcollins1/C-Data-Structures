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

void resizeCapacity(vec_t* vec, size_t capacity) {
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

void pushBack(vec_t* vec, void* data) {
    if (vec->size == vec->capacity) {
        resizeCapacity(vec, 2 * vec->capacity);
    }

    vec->dataArray[vec->size] = malloc(vec->dataSize);
    memcpy(vec->dataArray[vec->size], data, vec->dataSize);
    ++vec->size;
}

void clearVec(vec_t *vec, clearCallback func) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (func != NULL)
            func(vec->dataArray[i]);

        free(vec->dataArray[i]);
    }
    vec->size = 0;
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
