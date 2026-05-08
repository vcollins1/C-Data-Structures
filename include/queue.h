#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"
#include "list.h"

typedef ds_list_t ds_queue_t;

ds_queue_t* queue_create(size_t data_size);
void queue_destroy(ds_queue_t* queue, clear_callback func);
ds_status_code_t queue_enqueue(ds_queue_t* queue, void* data);

// removes data from the front of the queue
ds_status_code_t queue_dequeue(ds_queue_t* queue, clear_callback func);

// access data at front of queue without removal
ds_status_code_t queue_front(ds_queue_t* queue, void* output);

size_t queue_size(ds_queue_t* queue);
bool queue_empty(ds_queue_t* queue);

#endif
