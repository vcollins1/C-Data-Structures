#ifndef CDATASTRUCTURES_INT_LIST_H
#define CDATASTRUCTURES_INT_LIST_H

#include <stddef.h>
#include <stdint.h>
#include "list.h"

typedef ds_list_t int_list_t;
int_list_t *int_list_create(void);
void int_list_destroy(int_list_t *list);

int32_t int_list_add_back(int_list_t *list, int32_t data);
int32_t int_list_remove_back(int_list_t *list);

size_t int_list_size(int_list_t *list);
void int_list_print(int_list_t *list);

#endif //CDATASTRUCTURES_INT_LIST_H
