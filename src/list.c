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
    size_t dataSize;
    Node* head;
    Node* tail;
};

struct ListIterator {
    size_t dataSize;
    Node* current;
};

list_t* createList(size_t dataSize) {
    list_t* list = malloc(sizeof(list_t));
    if (!list) return NULL;

    list->size = 0;
    list->dataSize = dataSize;
    list->head = list->tail = NULL;
    
    return list;
}

void destroyList(list_t *list, clearCallback func) {
    clearList(list, func);
    free(list->head);
    free(list->tail);
    free(list);
}

Node* createListNode(void* data, size_t dataSize) {
    Node* newNode = malloc(sizeof(Node));
    if (!newNode) return NULL;
    newNode->next = NULL;
    
    newNode->data = malloc(dataSize);
    if (!newNode->data) {
        free(newNode);
        return NULL;
    }

    memcpy(newNode->data, data, dataSize);
    return newNode;
}

// Add element to the front of list
ListStatusCode unshift(list_t* list, void *data) {
    Node* newNode = createListNode(data, list->dataSize);
    if (!newNode) return ListMemoryError;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }

    ++list->size;
    return ListOperationSuccess;
}

ListStatusCode addBack(list_t *list, void *data) {
    Node* newNode = createListNode(data, list->dataSize);
    if (!newNode) return ListMemoryError;

    if (list->size == 0) {
        list->head = list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    ++list->size;
    return ListOperationSuccess;
}

ListStatusCode insertAt(list_t *list, size_t index,  void *data) {
    if (index > list->size) return ListIndexError;

    if (index == 0) {
        return unshift(list, data);
    } else if (index == list->size) {
        return addBack(list, data);
    } else {
        Node* newNode = createListNode(data, list->dataSize);
        if (!newNode) return ListMemoryError;

        Node* current = list->head;
        for (size_t i = 1; i < index; ++i)
            current = current->next;

        newNode->next = current->next;
        current->next = newNode;
    }

    ++list->size;
    return ListOperationSuccess;
}

ListStatusCode shift(list_t *list, void *output) {
    if (list->size == 0) return ListEmptyError;

    Node* delete = list->head;
    memcpy(output, delete->data, list->dataSize);

    if (list->size == 1) {
        list->head = list->tail = NULL;
    } else {
        list->head = list->head->next;
    }

    free(delete->data);
    free(delete);
    --list->size;
    return ListOperationSuccess;
}

ListStatusCode removeBack(list_t* list, void *output) {
    if (list->size == 0) return ListEmptyError;

    Node* delete = list->tail;
    memcpy(output, list->tail->data, list->dataSize);

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
    return ListOperationSuccess;
}

ListStatusCode removeAt(list_t* list, size_t index, void *output) {
    if (list->size == 0) return ListEmptyError;
    if (index >= list->size) return ListIndexError;

    if (index == 0) {
        return shift(list, output);
    } else if (index == list->size - 1) {
        return removeBack(list, output);
    } else {
        Node* previous = NULL;
        Node* delete = list->head;
        for (size_t i = 0; i < index; ++i) {
            previous = delete;
            delete = delete->next;
        }
        previous->next = delete->next;

        memcpy(output, delete->data, list->dataSize);
        free(delete->data);
        free(delete);
    }

    --list->size;
    return ListOperationSuccess;
}

void clearList(list_t* list, clearCallback func) {
    while (list->head) {
        Node* current = list->head;
        list->head = list->head->next;
        if (func == NULL)
            free(current->data);
        else
            func(current->data);

        free(current);
    }
    list->size = 0;
    list->head = list->tail = NULL;
}

size_t listSize(list_t* list)
{
    return list->size;
}

bool isListEmpty(list_t* list) {
    return list->size == 0;
}

ListStatusCode find(list_t* list, void* key, void* found, findCallback func) {
    if (list->size == 0 || !key) return ListEmptyError;

    Node* current = list->head;
    while (current) {
        if (func(current->data, key)) {
            memcpy(found, current->data, list->dataSize);
            return ListOperationSuccess;
        }

        current = current->next;
    }

    return ListNotFoundError;
}

ListStatusCode set(list_t* list, size_t index, void* update) {
    if (list->size == 0) return ListEmptyError;
    if (index >= list->size) return ListIndexError;

    Node* current = list->head;
    for (size_t i = 0; i < index; ++i)
        current = current->next;

    memcpy(current->data, update, list->dataSize);
    return ListOperationSuccess;
}

listIter_t* createListIterator(list_t* list) {
    listIter_t* iter = malloc(sizeof(listIter_t));
    iter->current = list->head;
    iter->dataSize = list->dataSize;
    return iter;
}

void destroyListIterator(listIter_t *iter) {
    free(iter);
}

void listIteratorNext(listIter_t* iter) {
    if (iter->current) {
        iter->current = iter->current->next;
    }
}

void getListIteratorData(listIter_t *iter, void *output) {
    if (iter->current) {
        memcpy(output, iter->current->data, iter->dataSize);
    }
}

bool hasNext(listIter_t* iter) {
    return iter->current != NULL;;
}

void printList(list_t* list, printCallback func) {
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
