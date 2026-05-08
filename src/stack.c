#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "vector.h"

ds_stack_t* stack_create(size_t data_size) {
   ds_stack_t* stack = vector_create(data_size);
   return stack;
}

void stack_destroy(ds_stack_t* stack, clear_callback func) {
   vector_destroy(stack, func);
}

ds_status_code_t stack_push(ds_stack_t* stack, void* data) {
   return vector_push_back(stack, data);
}

ds_status_code_t stack_pop(ds_stack_t* stack, clear_callback func) {
   return vector_pop_back(stack, func);
}

ds_status_code_t stack_top(ds_stack_t* stack, void* output) {
   return vector_back(stack, output);
}

size_t stack_size(ds_stack_t* stack) {
   return vector_size(stack);
}

bool stack_empty(ds_stack_t* stack) {
   return vector_empty(stack);
}
