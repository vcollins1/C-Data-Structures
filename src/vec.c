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

struct VecIter {
    size_t dataSize;
    size_t current;
    size_t last;
    void** data;
};

DS_StatusCode_t resizeCapacity(vec_t* vec, size_t capacity) {
    if (vec->size == 0) capacity = 1;

    void** newDataArray = malloc(sizeof(*vec->dataArray) * capacity);
    if (newDataArray == NULL) return DS_MEMORY_ERROR;

    memcpy(newDataArray, vec->dataArray, sizeof(*vec->dataArray) * vec->size);

    free(vec->dataArray);
    vec->dataArray = newDataArray;
    vec->capacity = capacity;
    return DS_SUCCESS_OK;
}

vec_t* vec_create(size_t dataSize) {
    vec_t* vec = malloc(sizeof(vec_t));
    if (!vec) return NULL;

    vec->capacity = 1;
    vec->size = 0;
    vec->dataSize = dataSize;
    vec->dataArray = malloc(sizeof(*vec->dataArray) * vec->capacity);
    if (!vec->dataArray) {
        free(vec);
        return NULL;
    }

    return vec;
}

void vec_destroy(vec_t* vec, clear_callback func) {
    vec_clear(vec, func);
    free(vec->dataArray);
    free(vec);
}

DS_StatusCode_t vec_push_back(vec_t* vec, void* data) {
    if (vec->size == vec->capacity) {
        resizeCapacity(vec, 2 * vec->capacity);
    }

    vec->dataArray[vec->size] = malloc(vec->dataSize);
    if (!vec->dataArray[vec->size]) return DS_MEMORY_ERROR;

    if (!vec->dataArray[vec->size])
        return DS_MEMORY_ERROR;

    memcpy(vec->dataArray[vec->size], data, vec->dataSize);
    ++vec->size;
    return DS_SUCCESS_OK;
}

DS_StatusCode_t vec_insert(vec_t* vec, size_t index, void* data) {
    if (index > vec->size) return DS_INDEX_ERROR;
    if (vec->size == vec->capacity) {
        DS_StatusCode_t status = resizeCapacity(vec, 2 * vec->capacity);
        if(status != DS_SUCCESS_OK)
            return status;
    }
        

    vec->dataArray[vec->size] = malloc(vec->dataSize);
    if (!vec->dataArray[vec->size])
        return DS_MEMORY_ERROR;

    for (size_t i = vec->size; i > index; --i) {
        memcpy(vec->dataArray[i], vec->dataArray[i - 1], vec->dataSize);
    }
    
    memcpy(vec->dataArray[index], data, vec->dataSize);
    ++vec->size;
    return DS_SUCCESS_OK;
}

DS_StatusCode_t vec_pop_back(vec_t* vec, void *output) {
    if (vec->size == 0) return DS_EMPTY_ERROR;

    --vec->size;
    memcpy(output, vec->dataArray[vec->size], vec->dataSize);
    free(vec->dataArray[vec->size]);

    if (vec->size == vec->capacity/4) {
        DS_StatusCode_t status = resizeCapacity(vec, vec->capacity/2);
        if(status != DS_SUCCESS_OK)
            return status;
    }

    return DS_SUCCESS_OK;
}

void vec_clear(vec_t *vec, clear_callback func) {
    for (size_t i = 0; i < vec->size; ++i) {
        if (func != NULL)
            func(vec->dataArray[i]);

        free(vec->dataArray[i]);
    }
    vec->size = 0;
}

size_t vec_size(vec_t* vec) {
    return vec->size;
}

size_t vec_capacity(vec_t* vec) {
    return vec->capacity;
}

DS_StatusCode_t vec_front(vec_t* vec, void* output) {
    if (vec->size == 0) return DS_EMPTY_ERROR;
    memcpy(output, vec->dataArray[0], vec->dataSize);
    return DS_SUCCESS_OK;
}

DS_StatusCode_t vec_back(vec_t* vec, void* output) {
    if (vec->size == 0) return DS_EMPTY_ERROR;
    memcpy(output, vec->dataArray[vec->size - 1], vec->dataSize);
    return DS_SUCCESS_OK;
}

DS_StatusCode_t vec_at(vec_t* vec, size_t index, void* output) {
    if (vec->size == 0) return DS_EMPTY_ERROR;
    if (index >= vec->size) return DS_INDEX_ERROR;
    memcpy(output, vec->dataArray[index], vec->dataSize);
    return DS_SUCCESS_OK;
}

vecIter_t* vec_create_iter(vec_t* vec) {
    vecIter_t* iter = malloc(sizeof(vecIter_t));
    if (!iter) return NULL;

    iter->dataSize = vec->dataSize;
    iter->current = 0;
    iter->last = vec->size;

    iter->data = malloc(sizeof(vec->dataArray) * vec->size);
    if (!iter->data) {
        free(iter);
        return NULL;
    }
    memcpy(iter->data, vec->dataArray, sizeof(*vec->dataArray) * vec->size);

    return iter;
}

void vec_destroy_iter(vecIter_t* iter) {
    free(iter->data);
    free(iter);
}

void vec_iter_next(vecIter_t* iter) {
    iter->current++;
}

void get_vec_iter_data(vecIter_t* iter, void *output) {
    memcpy(output, iter->data[iter->current], iter->dataSize);
}

bool vec_iter_has_next(vecIter_t* iter) {
    return iter->current < iter->last;
}

void vec_print(vec_t* vec, print_callback func) {
    printf("[");
    char* sep = "";
    for (size_t i = 0; i < vec->size; ++i) {
        printf("%s", sep);
        func(vec->dataArray[i]);
        sep = ", ";
    }
    printf("]\n");
}
