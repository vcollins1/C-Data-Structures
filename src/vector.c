#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

struct Vector {
    size_t capacity;
    size_t size;
    size_t data_size;
    void** data_array;
};

struct VectorIter {
    size_t data_size;
    size_t current;
    size_t last;
    void** data;
};

ds_status_code_t vector_resize_capacity(ds_vector_t* vector, size_t capacity) {
    if (vector->size == 0) capacity = 1;

    void** new_data_array = malloc(sizeof(*vector->data_array) * capacity);
    if (new_data_array == NULL) return DS_MEMORY_ERROR;

    memcpy(new_data_array, vector->data_array, sizeof(*vector->data_array) * vector->size);

    free(vector->data_array);
    vector->data_array = new_data_array;
    vector->capacity = capacity;
    return DS_SUCCESS_OK;
}

ds_vector_t* vector_create(size_t data_size) {
    ds_vector_t* vector = malloc(sizeof(ds_vector_t));
    if (!vector) return NULL;

    vector->capacity = 1;
    vector->size = 0;
    vector->data_size = data_size;
    vector->data_array = malloc(sizeof(*vector->data_array) * vector->capacity);
    if (!vector->data_array) {
        free(vector);
        return NULL;
    }

    return vector;
}

void vector_destroy(ds_vector_t* vector, clear_callback func) {
    vector_clear(vector, func);
    free(vector->data_array);
    free(vector);
}

ds_status_code_t vector_push_back(ds_vector_t* vector, void* data) {
    if (vector->size == vector->capacity) {
        ds_status_code_t status = vector_resize_capacity(vector, 2 * vector->capacity);
        if(status != DS_SUCCESS_OK)
            return status;
    }

    vector->data_array[vector->size] = malloc(vector->data_size);
    if (!vector->data_array[vector->size]) return DS_MEMORY_ERROR;

    memcpy(vector->data_array[vector->size], data, vector->data_size);
    ++vector->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t vector_insert(ds_vector_t* vector, size_t index, void* data) {
    if (index > vector->size) return DS_INDEX_ERROR;
    if (vector->size == vector->capacity) {
        ds_status_code_t status = vector_resize_capacity(vector, 2 * vector->capacity);
        if(status != DS_SUCCESS_OK)
            return status;
    }
        

    vector->data_array[vector->size] = malloc(vector->data_size);
    if (!vector->data_array[vector->size])
        return DS_MEMORY_ERROR;

    for (size_t i = vector->size; i > index; --i) {
        memcpy(vector->data_array[i], vector->data_array[i - 1], vector->data_size);
    }
    
    memcpy(vector->data_array[index], data, vector->data_size);
    ++vector->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t vector_pop_back(ds_vector_t* vector, clear_callback func) {
    if (vector->size == 0) return DS_EMPTY_ERROR;

    if ((vector->capacity > 1) && vector->size - 1 == vector->capacity/4) {
        ds_status_code_t status = vector_resize_capacity(vector, vector->capacity/2);
        if(status != DS_SUCCESS_OK)
            return status;
    }

    if (func) func(vector->data_array[vector->size - 1]);
    free(vector->data_array[--vector->size]);

    return DS_SUCCESS_OK;
}

void vector_clear(ds_vector_t *vector, clear_callback func) {
    for (size_t i = 0; i < vector->size; ++i) {
        if (func != NULL)
            func(vector->data_array[i]);

        free(vector->data_array[i]); 
    }
    vector->size = 0;
}

size_t vector_size(ds_vector_t* vector) {
    return vector->size;
}

size_t vector_capacity(ds_vector_t* vector) {
    return vector->capacity;
}

bool vector_empty(ds_vector_t* vector) {
    return vector->size == 0;
}

ds_status_code_t vector_front(ds_vector_t* vector, void* output) {
    if (vector->size == 0) return DS_EMPTY_ERROR;
    memcpy(output, vector->data_array[0], vector->data_size);
    return DS_SUCCESS_OK;
}

ds_status_code_t vector_back(ds_vector_t* vector, void* output) {
    if (vector->size == 0) return DS_EMPTY_ERROR;
    memcpy(output, vector->data_array[vector->size - 1], vector->data_size);
    return DS_SUCCESS_OK;
}

ds_status_code_t vector_at(ds_vector_t* vector, size_t index, void* output) {
    if (vector->size == 0) return DS_EMPTY_ERROR;
    if (index >= vector->size) return DS_INDEX_ERROR;
    memcpy(output, vector->data_array[index], vector->data_size);
    return DS_SUCCESS_OK;
}

ds_vector_iter_t* vector_create_iter(ds_vector_t* vector) {
    if (vector->size == 0) return NULL;
    ds_vector_iter_t* iter = malloc(sizeof(ds_vector_iter_t));
    if (!iter) return NULL;

    iter->data_size = vector->data_size;
    iter->current = 0;
    iter->last = vector->size;

    iter->data = malloc(sizeof(vector->data_array) * vector->size);
    if (!iter->data) {
        free(iter);
        return NULL;
    }
    memcpy(iter->data, vector->data_array, sizeof(*vector->data_array) * vector->size);

    return iter;
}

void vector_destroy_iter(ds_vector_iter_t* iter) {
    free(iter->data);
    free(iter);
}

void vector_iter_next(ds_vector_iter_t* iter) {
    iter->current++;
}

void get_vector_iter_data(ds_vector_iter_t* iter, void *output) {
    memcpy(output, iter->data[iter->current], iter->data_size);
}

bool vector_iter_has_next(ds_vector_iter_t* iter) {
    return iter->current < iter->last;
}

void vector_print(ds_vector_t* vector, print_callback func) {
    printf("[");
    char* sep = "";
    for (size_t i = 0; i < vector->size; ++i) {
        printf("%s", sep);
        func(vector->data_array[i]);
        sep = ", ";
    }
    printf("]\n");
}
