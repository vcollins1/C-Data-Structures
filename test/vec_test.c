#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "vec.h"

void testVecElementAdd(void) {
    vec_t* vec = createVec(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, f = 10, g = 11, h = 808;
    pushBack(vec, &a);
    CU_ASSERT(vecSize(vec) == 1);
    CU_ASSERT(vecCapacity(vec) == 1);

    pushBack(vec, &b);
    CU_ASSERT(vecSize(vec) == 2);
    CU_ASSERT(vecCapacity(vec) == 2);

    pushBack(vec, &c);
    CU_ASSERT(vecSize(vec) == 3);
    CU_ASSERT(vecCapacity(vec) == 4);

    pushBack(vec, &d);
    CU_ASSERT(vecSize(vec) == 4);
    CU_ASSERT(vecCapacity(vec) == 4);

    insert(vec, 0, &e);
    CU_ASSERT(vecSize(vec) == 5);
    CU_ASSERT(vecCapacity(vec) == 8);

    insert(vec, 5, &f);
    CU_ASSERT(vecSize(vec) == 6);
    CU_ASSERT(vecCapacity(vec) == 8);

    insert(vec, 2, &g);
    CU_ASSERT(vecSize(vec) == 7);
    CU_ASSERT(vecCapacity(vec) == 8);

    CU_ASSERT(insert(vec, 8, &h) == VecIndexError);
    CU_ASSERT(vecSize(vec) == 7);
    CU_ASSERT(vecCapacity(vec) == 8);

    destroyVec(vec, NULL);
}

void testVecElementRemove(void) {
    vec_t* vec = createVec(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output;
    pushBack(vec, &a);
    pushBack(vec, &b);
    pushBack(vec, &c);
    pushBack(vec, &d);
    pushBack(vec, &e);

    popBack(vec, &output);
    CU_ASSERT(output == 1000);
    CU_ASSERT(vecSize(vec) == 4);

    popBack(vec, &output);
    CU_ASSERT(output == 90);
    CU_ASSERT(vecSize(vec) == 3);

    popBack(vec, &output);
    CU_ASSERT(output == 101);
    CU_ASSERT(vecSize(vec) == 2);
    CU_ASSERT(vecCapacity(vec) == 4);

    popBack(vec, &output);
    CU_ASSERT(output == 100);
    CU_ASSERT(vecSize(vec) == 1);
    CU_ASSERT(vecCapacity(vec) == 2);

    popBack(vec, &output);
    CU_ASSERT(output == 47);
    CU_ASSERT(vecSize(vec) == 0);
    CU_ASSERT(vecCapacity(vec) == 1);

    CU_ASSERT(popBack(vec, &output) == VecEmptyError);

    destroyVec(vec, NULL);
}

void testVecIterator(void) {
    vec_t* vec = createVec(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output, i = 0;
    pushBack(vec, &a);
    pushBack(vec, &b);
    pushBack(vec, &c);
    pushBack(vec, &d);
    pushBack(vec, &e);

    vecIter_t* iter = createVecIterator(vec);
    int expected[] = {47, 100, 101, 90, 1000};

    while (vecIterHasNext(iter)) {
        getVecIteratorData(iter, &output);
        CU_ASSERT(output == expected[i++]);
        vecIteratorNext(iter);
    }

    destroyVecIterator(iter);
    destroyVec(vec, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite suiteVecTest = CU_add_suite("Vec Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(suiteVecTest, "Test for adding elements to a vec type", testVecElementAdd);
    CU_add_test(suiteVecTest, "Test for removing elements to a vec type", testVecElementRemove);
    CU_add_test(suiteVecTest, "Test Vec iterator", testVecIterator);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
