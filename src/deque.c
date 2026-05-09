#include "deque.h"
#include "list.h"

ds_deque_t* deque_create(size_t data_size) {
    return NULL;
}

void deque_destroy(ds_deque_t* deque, clear_callback func) {

}

size_t deque_size(ds_deque_t *deque) {
    return 0;
}

bool deque_empty(ds_deque_t* deque) {
    return false;
}

ds_status_code_t deque_front(ds_deque_t* deque, void* output) {
    return DS_SUCCESS_OK;
}

ds_status_code_t deque_back(ds_deque_t* deque, void* output) {
    return DS_SUCCESS_OK;
}

ds_status_code_t deque_push_front(ds_deque_t* deque, void* data) {
    return DS_SUCCESS_OK;
}

ds_status_code_t deque_push_back(ds_deque_t* deque, void* data) {
    return DS_SUCCESS_OK;
}

ds_status_code_t deque_pop_front(ds_deque_t* deque, clear_callback func) {
    return DS_SUCCESS_OK;
}

ds_status_code_t deque_pop_back(ds_deque_t*  deque, clear_callback func) {
    return DS_SUCCESS_OK;
}
