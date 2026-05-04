#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"

typedef struct StackDS stackDS_t;

stackDS_t* stack_create(size_t data_size);
void stack_destroy(stackDS_t* stack, clear_callback func);
DS_StatusCode_t stack_push(stackDS_t* stack, void* data);
DS_StatusCode_t stack_pop(stackDS_t* stack);
DS_StatusCode_t stack_top(stackDS_t* stack, void* output);
size_t stack_size(stackDS_t* stack);
bool stack_empty(stackDS_t* stack);

#endif
