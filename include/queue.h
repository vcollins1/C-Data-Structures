#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"

typedef struct QueueDS queueDS_t;

queueDS_t* queue_create(size_t data_size);
void queue_destroy(queueDS_t* queue, clear_callback func);
DS_StatusCode_t queue_enqueue(queueDS_t* queue, void* data);
DS_StatusCode_t queue_dequeue(queueDS_t* queue, void* output, clear_callback func);
size_t queue_size(queueDS_t* queue);
bool queue_empty(queueDS_t* queue);

#endif
