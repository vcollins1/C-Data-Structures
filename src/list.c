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

list_t* list_create(size_t data_size) {
    list_t* list = malloc(sizeof(list_t));
    if (!list) return NULL;

    list->size = 0;
    list->data_size = data_size;
    list->head = list->tail = NULL;
    
    return list;
}

void list_destroy(list_t *list, clear_callback func) {
    list_clear(list, func);
    free(list->head);
    free(list->tail);
    free(list);
}

Node* createListNode(void* data, size_t data_size) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->next = NULL;
    
    newNode->data = malloc(data_size);
    if (!newNode->data) {
        free(newNode);
        return NULL;
    }

    memcpy(newNode->data, data, data_size);
    return newNode;
}

// Add element to the front of list
DS_StatusCode_t list_unshift(list_t* list, void *data) {
    Node* newNode = createListNode(data, list->data_size);
    if (!newNode) return DS_MEMORY_ERROR;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

DS_StatusCode_t list_add_back(list_t *list, void *data) {
    Node* newNode = createListNode(data, list->data_size);
    if (!newNode) return DS_MEMORY_ERROR;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

DS_StatusCode_t list_insert_at(list_t *list, size_t index,  void *data) {
    if (index > list->size) return DS_INDEX_ERROR;

    if (index == 0) {
        return list_unshift(list, data);
    } else if (index == list->size) {
        return list_add_back(list, data);
    } else {
        Node* newNode = createListNode(data, list->data_size);
        if (!newNode) return DS_MEMORY_ERROR;

        Node* current = list->head;
        for (size_t i = 1; i < index; ++i)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    ++list->size;
    return DS_SUCCESS_OK;
}

DS_StatusCode_t list_shift(list_t *list, void *output) {
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

DS_StatusCode_t list_remove_back(list_t* list, void *output) {
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

DS_StatusCode_t list_remove_at(list_t* list, size_t index, void *output) {
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

void list_clear(list_t* list, clear_callback func) {
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

size_t list_size(list_t* list)
{
    return list->size;
}

bool is_list_empty(list_t* list) {
    return list->size == 0;
}

DS_StatusCode_t list_find(list_t* list, void* key, void* found, find_callback func) {
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

DS_StatusCode_t list_set(list_t* list, size_t index, void* update) {
    if (list->size == 0) return DS_EMPTY_ERROR;
    if (index >= list->size) return DS_INDEX_ERROR;

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i)
        current = current->next;

    memcpy(current->data, update, list->data_size);
    return DS_SUCCESS_OK;
}

listIter_t* list_create_iter(list_t* list) {
    listIter_t* iter = malloc(sizeof(listIter_t));
    iter->current = list->head;
    iter->data_size = list->data_size;
    return iter;
}

void list_destroy_iter(listIter_t *iter) {
    free(iter);
}

void list_iter_next(listIter_t* iter) {
    if (iter->current) {
        iter->current = iter->current->next;
    }
}

void get_list_iter_data(listIter_t *iter, void *output) {
    if (iter->current) {
        memcpy(output, iter->current->data, iter->data_size);
    }
}

bool list_iter_has_next(listIter_t* iter) {
    return iter->current != NULL;;
}

void list_print(list_t* list, print_callback func) {
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
