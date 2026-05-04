#ifndef STACK_H
#define STACK_H

#include <stdbool.h>
#include <stddef.h>
#include "ds_utils.h"

typedef struct Stack stack_t;

stack_t* stack_create(size_t data_size);
void stack_destroy(stack_t* stack);
DS_StatusCode_t stack_push(stack_t* stack, void* data);
DS_StatusCode_t stack_pop(stack_t* stack);
DS_StatusCode_t stack_top(stack_t* stack, void* output);
size_t stack_size(stack_t* stack);
bool stack_empty(stack_t* stack);

#endif