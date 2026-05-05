#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct StackDS {
   size_t size;
   size_t capacity;
   size_t data_size;
   void** data; 
};

DS_StatusCode_t stack_resize(stackDS_t* stack, size_t capacity) {
   if (stack->size == 0) capacity = 1;

   void** new_data = malloc(capacity * sizeof(*stack->data));
   if (!new_data) return DS_MEMORY_ERROR;

   memmove(new_data, stack->data, stack->size * sizeof(*stack->data));
   free(stack->data);
   stack->data = new_data;
   stack->capacity = capacity;
   return DS_SUCCESS_OK;
}

stackDS_t* stack_create(size_t data_size) {
   stackDS_t* stack = malloc(sizeof(stackDS_t));
   if (!stack) return NULL;

   stack->data = malloc(sizeof(*stack->data));
   if (!stack->data) {
      free(stack);
      return NULL;
   }

   stack->data_size = data_size;
   stack->capacity = 1;
   stack->size = 0;

   return stack;
}

void stack_destroy(stackDS_t* stack, clear_callback func) {
   while (stack->size > 0) {
      if (func != NULL)
         func(stack->data[stack->size - 1]);

      free(stack->data[--stack->size]);
   }

   free(stack->data);
   free(stack);
}

DS_StatusCode_t stack_push(stackDS_t* stack, void* data) {
   if (stack->capacity == stack->size && stack_resize(stack, stack->capacity * 2) != DS_SUCCESS_OK)
      return DS_MEMORY_ERROR;

   stack->data[stack->size] = malloc(stack->data_size);
   if (!stack->data[stack->size]) return DS_MEMORY_ERROR;

   memcpy(stack->data[stack->size++], data, stack->data_size);

   return DS_SUCCESS_OK;
}

DS_StatusCode_t stack_pop(stackDS_t* stack) {
   if (stack->size == 0) return DS_EMPTY_ERROR;

   free(stack->data[--stack->size]);

   if (stack->capacity / 4 == stack->size && stack_resize(stack, stack->capacity / 2) != DS_SUCCESS_OK)
      return DS_MEMORY_ERROR;
   
   return DS_SUCCESS_OK;
}

DS_StatusCode_t stack_top(stackDS_t* stack, void* output) {
   if (stack->size == 0) return DS_EMPTY_ERROR;

   memcpy(output, stack->data[stack->size - 1], stack->data_size);

   return DS_SUCCESS_OK;
}

size_t stack_size(stackDS_t* stack) {
   return stack->size;
}

bool stack_empty(stackDS_t* stack) {
   return stack->size == 0;
}
