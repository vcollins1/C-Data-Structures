#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "list.h"

bool findInt(void* a, void* key) {
    return *(int*)a == *(int*)key;
}

void testInserts(void) {
    list_t* list = createList(sizeof(int));

    int data = 10;
    insertAt(list, 0, &data);
    CU_ASSERT(listSize(list) == 1);

    unshift(list, &data);
    CU_ASSERT(listSize(list) == 2);

    data = 100;
    addBack(list, &data);
    CU_ASSERT(listSize(list) == 3);

    data = 25;
    insertAt(list, 1, &data);
    CU_ASSERT(listSize(list) == 4);

    data = 1000;
    CU_ASSERT(insertAt(list, 6, &data) == ListIndexError);

    destroyList(list, NULL);
}

void testRemoves(void) {
    list_t* list = createList(sizeof(int));
    int data = 10;
    unshift(list, &data);
    data = 100;
    addBack(list, &data);
    data = 25;
    insertAt(list, 1, &data);

    int output;
    removeAt(list, 1, &output);
    CU_ASSERT(output == 25);

    shift(list, &output);
    CU_ASSERT(output == 10);

    CU_ASSERT(removeAt(list, 1, &output) == ListIndexError);

    removeBack(list, &output);
    CU_ASSERT(output == 100);

    CU_ASSERT(shift(list, &output) == ListEmptyError);
    CU_ASSERT(removeBack(list, &output) == ListEmptyError);
    CU_ASSERT(removeAt(list, 0, &output) == ListEmptyError);

    destroyList(list, NULL);
}

void testUtils(void) {
    list_t* list = createList(sizeof(int));
    int data = 100;
    addBack(list, &data);
    data = 200;
    addBack(list, &data);
    data = 300;
    addBack(list, &data);

    // Test for find function
    int key = 200, output;
    CU_ASSERT(find(list, &key, &output, findInt) == ListOperationSuccess);

    key = 10;
    CU_ASSERT(find(list, &key, &output, findInt) == ListNotFoundError);

    // Test for set function
    int newValue = 47;
    CU_ASSERT(set(list, 1, &newValue) == ListOperationSuccess);
    removeAt(list, 1, &output);
    CU_ASSERT(output == newValue);

    // Test list size
    CU_ASSERT(listSize(list) == 2);

    // Test clear list
    clearList(list, NULL);
    CU_ASSERT(isListEmpty(list) == true);
    CU_ASSERT(listSize(list) == 0);

    destroyList(list, NULL);
}

void testIterator(void) {
    list_t* list = createList(sizeof(int));

    int a = 1, b = 2, c = 3;
    unshift(list, &a);
    unshift(list, &b);
    unshift(list, &c);

    listIter_t* iter = createListIterator(list);
    int data, currentValue = 0;
    int expectedValues[] = {3, 2, 1};
    
    while (hasNext(iter)) {
        getListIteratorData(iter, &data);
        CU_ASSERT(data == expectedValues[currentValue++]);
        listIteratorNext(iter);
    }
    
    destroyListIterator(iter);
    destroyList(list, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite suiteListTest = CU_add_suite("List Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(suiteListTest, "list insert tests", testInserts);
    CU_add_test(suiteListTest, "list remove tests", testRemoves);
    CU_add_test(suiteListTest, "List utils tests", testUtils);
    CU_add_test(suiteListTest, "List iterator tests", testIterator);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
