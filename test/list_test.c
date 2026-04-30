#include <CUnit/Basic.h>
#include <stdlib.h>
#include "list.h"

list_t* list;

int initFunc(void) {
    list = createList(sizeof(int));
    if (!list) return 1;

    return 0;
}

int cleanFunc(void) {
    destroyList(list, NULL);
    return 0;
}

bool findInt(void* a, void* key) {
    return *(int*)a == *(int*)key;
}

void testInserts(void) {
    int data = 10;
    unshift(list, &data);
    CU_ASSERT(listSize(list) == 1);

    data = 100;
    addBack(list, &data);
    CU_ASSERT(listSize(list) == 2);

    data = 25;
    insertAt(list, 1, &data);
    CU_ASSERT(listSize(list) == 3);

    data = 1000;
    CU_ASSERT(insertAt(list, 5, &data) == ListIndexError);
}

void testRemoves(void) {
    void* data = malloc(sizeof(int));
    removeAt(list, 1, data);
    CU_ASSERT(*(int*)data == 25);

    shift(list, data);
    CU_ASSERT(*(int*)data == 10);

    CU_ASSERT(removeAt(list, 1, data) == ListIndexError);

    removeBack(list, data);
    CU_ASSERT(*(int*)data == 100);

    CU_ASSERT(shift(list, data) == ListEmptyError);
    CU_ASSERT(removeBack(list, data) == ListEmptyError);
    CU_ASSERT(removeAt(list, 0, data) == ListEmptyError);
}

void testFind(void) {
    int data = 100;
    addBack(list, &data);
    data = 200;
    addBack(list, &data);
    data = 300;
    addBack(list, &data);

    int key = 200;
    void* output = malloc(sizeof(int));
    CU_ASSERT(find(list, &key, output, findInt) == ListOperationSuccess);

    key = 10;
    CU_ASSERT(find(list, &key, output, findInt) == ListNotFoundError);
}

void testClear(void) {
    CU_ASSERT(listSize(list) == 3);
    clearList(list, NULL);
    
    CU_ASSERT(listSize(list) == 0);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_pSuite suiteSLL = CU_add_suite("List Test Suite", initFunc, cleanFunc);
    if (!suiteSLL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suiteSLL, "list insert tests", testInserts)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suiteSLL, "list remove tests", testRemoves)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suiteSLL, "test find", testFind)) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (!CU_add_test(suiteSLL, "test clear", testClear)) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
