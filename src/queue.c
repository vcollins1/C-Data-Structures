#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"

ds_queue_t* queue_create(size_t data_size) {
    ds_queue_t* queue = list_create(data_size);
    return queue;
}

void queue_destroy(ds_queue_t* queue, clear_callback func) {
    list_destroy(queue, func);
}

ds_status_code_t queue_enqueue(ds_queue_t* queue, void* data) {
    return list_add_back(queue, data);
}

ds_status_code_t queue_dequeue(ds_queue_t* queue, clear_callback func) {
    return list_shift(queue, func);
}

ds_status_code_t queue_front(ds_queue_t* queue, void *output) {
    return list_front(queue, output);
}

size_t queue_size(ds_queue_t* queue) {
    return list_size(queue);
}

bool queue_empty(ds_queue_t* queue) {
    return list_empty(queue);
}
