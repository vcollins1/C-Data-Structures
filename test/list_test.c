#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "list.h"

bool findInt(void* a, void* key) {
    return *(int*)a == *(int*)key;
}

void testInserts(void) {
    ds_list_t* list = list_create(sizeof(int));

    int data = 10;
    list_insert_at(list, 0, &data);
    CU_ASSERT(list_size(list) == 1);

    list_unshift(list, &data);
    CU_ASSERT(list_size(list) == 2);

    data = 100;
    list_add_back(list, &data);
    CU_ASSERT(list_size(list) == 3);

    data = 25;
    list_insert_at(list, 1, &data);
    CU_ASSERT(list_size(list) == 4);

    data = 1000;
    CU_ASSERT(list_insert_at(list, 6, &data) == DS_INDEX_ERROR);

    list_destroy(list, NULL);
}

void testRemoves(void) {
    ds_list_t* list = list_create(sizeof(int));
    int data = 10;
    list_unshift(list, &data);
    data = 100;
    list_add_back(list, &data);
    data = 25;
    list_insert_at(list, 1, &data);

    int output;
    list_remove_at(list, 1, &output);
    CU_ASSERT(output == 25);

    list_shift(list, &output);
    CU_ASSERT(output == 10);

    CU_ASSERT(list_remove_at(list, 1, &output) == DS_INDEX_ERROR);

    list_remove_back(list, &output);
    CU_ASSERT(output == 100);

    CU_ASSERT(list_shift(list, &output) == DS_EMPTY_ERROR);
    CU_ASSERT(list_remove_back(list, &output) == DS_EMPTY_ERROR);
    CU_ASSERT(list_remove_at(list, 0, &output) == DS_EMPTY_ERROR);

    list_destroy(list, NULL);
}

void testUtils(void) {
    ds_list_t* list = list_create(sizeof(int));
    int data = 100;
    list_add_back(list, &data);
    data = 200;
    list_add_back(list, &data);
    data = 300;
    list_add_back(list, &data);

    // Test for find function
    int key = 200, output;
    CU_ASSERT(list_find(list, &key, &output, findInt) == DS_SUCCESS_OK);

    key = 10;
    CU_ASSERT(list_find(list, &key, &output, findInt) == DS_ELEMENT_NOT_FOUND);

    // Test for set function
    int new_value = 47;
    CU_ASSERT(list_set(list, 1, &new_value) == DS_SUCCESS_OK);
    list_remove_at(list, 1, &output);
    CU_ASSERT(output == new_value);

    // Test list size
    CU_ASSERT(list_size(list) == 2);

    // Test clear list
    list_clear(list, NULL);
    CU_ASSERT(is_list_empty(list) == true);
    CU_ASSERT(list_size(list) == 0);

    list_destroy(list, NULL);
}

void testIterator(void) {
    ds_list_t* list = list_create(sizeof(int));

    int a = 1, b = 2, c = 3;
    list_unshift(list, &a);
    list_unshift(list, &b);
    list_unshift(list, &c);

    ds_list_iter_t* iter = list_create_iter(list);
    int data, current_value = 0;
    int expected_values[] = {3, 2, 1};
    
    while (list_iter_has_next(iter)) {
        get_list_iter_data(iter, &data);
        CU_ASSERT(data == expected_values[current_value++]);
        list_iter_next(iter);
    }
    
    list_destroy_iter(iter);
    list_destroy(list, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite list_suite = CU_add_suite("List Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(list_suite, "list insert tests", testInserts);
    CU_add_test(list_suite, "list remove tests", testRemoves);
    CU_add_test(list_suite, "List utils tests", testUtils);
    CU_add_test(list_suite, "List iterator tests", testIterator);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
