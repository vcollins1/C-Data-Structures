#include <stdlib.h>
#include <string.h>
#include "stack.h"

struct Stack {
   size_t size;
   size_t capacity;
   size_t data_size;
   void** stack; 
};

stack_t* stack_create(size_t data_size) {
   return NULL;
}

void stack_destroy(stack_t* stack, clear_callback func) {

}

DS_StatusCode_t stack_push(stack_t* stack, void* data) {
   return DS_SUCCESS_OK;
}

DS_StatusCode_t stack_pop(stack_t* stack) {
   return DS_SUCCESS_OK;
}

DS_StatusCode_t stack_top(stack_t* stack, void* output) {
   return DS_SUCCESS_OK;
}

size_t stack_size(stack_t* stack) {
   return 0;
}

bool stack_empty(stack_t* stack) {
   return false;
}