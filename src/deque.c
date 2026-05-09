#include "deque.h"
#include "list.h"

ds_deque_t* deque_create(size_t data_size) {
    return list_create(data_size);
}

void deque_destroy(ds_deque_t* deque, clear_callback func) {
    list_destroy(deque, func);
}

size_t deque_size(ds_deque_t *deque) {
    return list_size(deque);
}

bool deque_empty(ds_deque_t* deque) {
    return list_empty(deque);
}

ds_status_code_t deque_front(ds_deque_t* deque, void* output) {
    return list_front(deque, output);
}

ds_status_code_t deque_back(ds_deque_t* deque, void* output) {
    return list_back(deque, output);
}

ds_status_code_t deque_push_front(ds_deque_t* deque, void* data) {
    return list_unshift(deque, data);
}

ds_status_code_t deque_push_back(ds_deque_t* deque, void* data) {
    return list_add_back(deque, data);
}

ds_status_code_t deque_pop_front(ds_deque_t* deque, clear_callback func) {
    return list_shift(deque, func);
}

ds_status_code_t deque_pop_back(ds_deque_t*  deque, clear_callback func) {
    return list_remove_back(deque, func);
}
