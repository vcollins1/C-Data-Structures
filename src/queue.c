#include "queue.h"

typedef struct Node {
    void* data;
    struct Node* previous;
    struct Node* next;
} Node;

struct QueueDS {
    size_t size;
    size_t data_size;
    Node* head;
    Node* tail;
};

queueDS_t* queue_create(size_t data_size) {
    return NULL;
}

void queue_destroy(queueDS_t* queue, clear_callback func) {

}

DS_StatusCode_t queue_enqueue(queueDS_t* queue, void* data) {
    return DS_SUCCESS_OK;
}

DS_StatusCode_t queue_dequeue(queueDS_t* queue, void* output) {
    return DS_SUCCESS_OK;
}

size_t queue_size(queueDS_t* queue) {
    return 0;
}

bool queue_empty(queueDS_t* queue) {
    return false;
}
