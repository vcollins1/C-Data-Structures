#include <stdlib.h>
#include <string.h>
#include "queue.h"

typedef struct Node {
    void* data;
    struct Node* previous;
    struct Node* next;
} Node;

struct Queue {
    size_t size;
    size_t data_size;
    Node* head;
    Node* tail;
};

Node* queue_node_create(void* data, size_t data_size) {
    Node* node = malloc(sizeof(Node));
    if (!node) return NULL;

    node->data = malloc(data_size);
    if (!node->data) {
        free(node);
        return NULL;
    }

    memcpy(node->data, data, data_size);
    node->previous = node->next = NULL;

    return node;
}

ds_queue_t* queue_create(size_t data_size) {
    ds_queue_t* queue = malloc(sizeof(ds_queue_t));
    if (!queue) return NULL;
    queue->head = queue->tail = NULL;
    queue->size = 0;
    queue->data_size = data_size;

    return queue;
}

void queue_destroy(ds_queue_t* queue, clear_callback func) {
    Node* current = queue->head;
    while (current) {
        Node* delete = current;
        current = current->next;
        if (func)
            func(delete->data);

        free(delete->data);
        free(delete);
    }

    queue->head = queue->tail = NULL;
    free(queue);
}

ds_status_code_t queue_enqueue(ds_queue_t* queue, void* data) {
    Node* node = queue_node_create(data, queue->data_size);
    if (!node)
        return DS_MEMORY_ERROR;

    if (queue->size == 0)
        queue->head = queue->tail = node;
    else {
        queue->tail->next = node;
        node->previous = queue->tail;
        queue->tail = node;
    }

    ++queue->size;
    return DS_SUCCESS_OK;
}

ds_status_code_t queue_dequeue(ds_queue_t* queue, void* output, clear_callback func) {
    if (queue->size == 0) return DS_EMPTY_ERROR;

    Node* delete_node = queue->head;

    if (queue->size == 1)
        queue->head = queue->tail = NULL;
    else {
        queue->head = queue->head->next;
        queue->head->previous = NULL;
    }

    memcpy(output, delete_node->data, queue->data_size);

    delete_node->next = NULL;
    if (func)
        func(delete_node->data);
    free(delete_node->data);
    free(delete_node);
    --queue->size;

    return DS_SUCCESS_OK;
}

size_t queue_size(ds_queue_t* queue) {
    return queue->size;
}

bool queue_empty(ds_queue_t* queue) {
    return queue->size == 0;
}
