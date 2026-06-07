#include "int_list.h"
#include <stdio.h>

int_list_t *int_list_create(void) {
    return list_create(sizeof(int32_t));
}

void int_list_destroy(int_list_t *list) {
    list_destroy(list, NULL);
}

int32_t int_list_add_back(int_list_t *list, int32_t data) {
    return list_add_back(list, &data);
}

int32_t int_list_remove_back(int_list_t *list) {
    return list_remove_back(list, NULL);
}

size_t int_list_size(int_list_t *list) {
    return list_size(list);
}

void int_list_print_callback(const void* data) {
    printf("%d", *(int32_t*)data);
}

void int_list_print(int_list_t *list) {
    list_print(list, int_list_print_callback);
}