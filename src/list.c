#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    void* data;
    struct Node* next;
} Node;

struct List {
    size_t size;
    size_t data_size;
    Node* head;
    Node* tail;
};

struct ListIter {
    size_t data_size;
    Node* current;
};

ds_list_t* list_create(size_t data_size) {
    ds_list_t* list = malloc(sizeof(ds_list_t));
    if (!list) return NULL;

    list->size = 0;
    list->data_size = data_size;
    list->head = list->tail = NULL;
    
    return list;
}

void list_destroy(ds_list_t *list, clear_callback func) {
    list_clear(list, func);
    free(list->head);
    free(list->tail);
    free(list);
}

Node* list_node_create(void* data, size_t data_size) {
    Node* new_node = malloc(sizeof(Node));
    if (!new_node) return NULL;
    new_node->next = NULL;
    
    new_node->data = malloc(data_size);
    if (!new_node->data) {
        free(new_node);
        return NULL;
    }

    memcpy(new_node->data, data, data_size);
    return new_node;
}

// Add element to the front of list
ds_status_code_t list_unshift(ds_list_t* list, void *data) {
    Node* new_node = list_node_create(data, list->data_size);
    if (!new_node) return DS_MEMORY_ERROR;

    if (list->size == 0) {
        list->head = list->tail = new_node;
    } else {
        new_node->next = list->head;
        list->head = new_node;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t list_add_back(ds_list_t *list, void *data) {
    Node* new_node = list_node_create(data, list->data_size);
    if (!new_node) return DS_MEMORY_ERROR;

    if (list->size == 0) {
        list->head = list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t list_insert_at(ds_list_t *list, size_t index,  void *data) {
    if (index > list->size) return DS_INDEX_ERROR;

    if (index == 0) {
        return list_unshift(list, data);
    } else if (index == list->size) {
        return list_add_back(list, data);
    } else {
        Node* new_node = list_node_create(data, list->data_size);
        if (!new_node) return DS_MEMORY_ERROR;

        Node* current = list->head;
        for (size_t i = 1; i < index; ++i)
            current = current->next;

        new_node->next = current->next;
        current->next = new_node;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t list_shift(ds_list_t *list, void *output) {
    if (list->size == 0) return DS_EMPTY_ERROR;

    Node* delete = list->head;
    memcpy(output, delete->data, list->data_size);

    if (list->size == 1) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
    }

    free(delete->data);
    free(delete);
    --list->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t list_remove_back(ds_list_t* list, void *output) {
    if (list->size == 0) return DS_EMPTY_ERROR;

    Node* delete = list->tail;
    memcpy(output, list->tail->data, list->data_size);

    if (list->size == 1) {
        list->head = list->tail = NULL;
    } else {
        Node* current = list->head;
        for (size_t i = 0; i < list->size - 2; ++i)
            current = current->next;

        current->next = NULL;
        list->tail = current;
    }

    free(delete->data);
    free(delete);
    --list->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t list_remove_at(ds_list_t* list, size_t index, void *output) {
    if (list->size == 0) return DS_EMPTY_ERROR;
    if (index >= list->size) return DS_INDEX_ERROR;

    if (index == 0) {
        return list_shift(list, output);
    } else if (index == list->size - 1) {
        return list_remove_back(list, output);
    } else {
        Node* previous = NULL;
        Node* delete = list->head;
        for (size_t i = 0; i < index; ++i) {
            previous = delete;
            delete = delete->next;
        }
        previous->next = delete->next;

        memcpy(output, delete->data, list->data_size);
        free(delete->data);
        free(delete);
    }

    --list->size;
    return DS_SUCCESS_OK;
}

void list_clear(ds_list_t* list, clear_callback func) {
    while (list->head) {
        Node* current = list->head;
        list->head = list->head->next;

        if (func != NULL)
            func(current->data);
            
        free(current->data);
        free(current);
    }

    list->size = 0;
    list->head = list->tail = NULL;
}

size_t list_size(ds_list_t* list)
{
    return list->size;
}

bool is_list_empty(ds_list_t* list) {
    return list->size == 0;
}

ds_status_code_t list_find(ds_list_t* list, void* key, void* found, find_callback func) {
    if (list->size == 0 || !key) return DS_EMPTY_ERROR;

    Node* current = list->head;
    while (current) {
        if (func(current->data, key)) {
            memcpy(found, current->data, list->data_size);
            return DS_SUCCESS_OK;
        }

        current = current->next;
    }

    return DS_ELEMENT_NOT_FOUND;
}

ds_status_code_t list_set(ds_list_t* list, size_t index, void* update) {
    if (list->size == 0) return DS_EMPTY_ERROR;
    if (index >= list->size) return DS_INDEX_ERROR;

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i)
        current = current->next;

    memcpy(current->data, update, list->data_size);
    return DS_SUCCESS_OK;
}

ds_list_iter_t* list_create_iter(ds_list_t* list) {
    ds_list_iter_t* iter = malloc(sizeof(ds_list_iter_t));
    iter->current = list->head;
    iter->data_size = list->data_size;
    return iter;
}

void list_destroy_iter(ds_list_iter_t *iter) {
    free(iter);
}

void list_iter_next(ds_list_iter_t* iter) {
    if (iter->current) {
        iter->current = iter->current->next;
    }
}

void get_list_iter_data(ds_list_iter_t *iter, void *output) {
    if (iter->current) {
        memcpy(output, iter->current->data, iter->data_size);
    }
}

bool list_iter_has_next(ds_list_iter_t* iter) {
    return iter->current != NULL;;
}

void list_print(ds_list_t* list, print_callback func) {
    Node* current = list->head;

    char* sep = "";
    printf("Size: %ld [", list->size);
    while (current) {
        printf("%s", sep);
        func(current->data);
        sep = ", ";
        current = current->next;
    }
    printf("]\n");
}
