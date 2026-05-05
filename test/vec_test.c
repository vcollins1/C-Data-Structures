#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "vec.h"

void testVecElementAdd(void) {
    vec_t* vec = vec_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, f = 10, g = 11, h = 808, output;
    vec_push_back(vec, &a);
    CU_ASSERT(vec_size(vec) == 1);
    CU_ASSERT(vec_capacity(vec) == 1);

    vec_push_back(vec, &b);
    CU_ASSERT(vec_size(vec) == 2);
    CU_ASSERT(vec_capacity(vec) == 2);

    vec_push_back(vec, &c);
    CU_ASSERT(vec_size(vec) == 3);
    CU_ASSERT(vec_capacity(vec) == 4);

    vec_push_back(vec, &d);
    CU_ASSERT(vec_size(vec) == 4);
    CU_ASSERT(vec_capacity(vec) == 4);

    vec_insert(vec, 0, &e);
    vec_front(vec, &output);
    CU_ASSERT(vec_size(vec) == 5);
    CU_ASSERT(vec_capacity(vec) == 8);
    CU_ASSERT(output == 1000);

    vec_insert(vec, 5, &f);
    vec_back(vec, &output);
    CU_ASSERT(vec_size(vec) == 6);
    CU_ASSERT(vec_capacity(vec) == 8);
    CU_ASSERT(output == 10);

    vec_insert(vec, 2, &g);
    vec_at(vec, 2, &output);
    CU_ASSERT(vec_size(vec) == 7);
    CU_ASSERT(vec_capacity(vec) == 8);
    CU_ASSERT(output == 11);

    CU_ASSERT(vec_insert(vec, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vec_at(vec, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vec_size(vec) == 7);
    CU_ASSERT(vec_capacity(vec) == 8);

    vec_destroy(vec, NULL);
}

void testVecElementRemove(void) {
    vec_t* vec = vec_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output;
    vec_push_back(vec, &a);
    vec_pop_back(vec, &output);
    CU_ASSERT(output == 47);
    CU_ASSERT(vec_size(vec) == 0);
    CU_ASSERT(vec_capacity(vec) == 1);


    vec_push_back(vec, &a);
    vec_push_back(vec, &b);
    vec_push_back(vec, &c);
    vec_push_back(vec, &d);
    vec_push_back(vec, &e);

    vec_pop_back(vec, &output);
    CU_ASSERT(output == 1000);
    CU_ASSERT(vec_size(vec) == 4);

    vec_pop_back(vec, &output);
    CU_ASSERT(output == 90);
    CU_ASSERT(vec_size(vec) == 3);

    vec_pop_back(vec, &output);
    CU_ASSERT(output == 101);
    CU_ASSERT(vec_size(vec) == 2);
    CU_ASSERT(vec_capacity(vec) == 4);

    vec_pop_back(vec, &output);
    CU_ASSERT(output == 100);
    CU_ASSERT(vec_size(vec) == 1);
    CU_ASSERT(vec_capacity(vec) == 2);

    vec_pop_back(vec, &output);
    CU_ASSERT(output == 47);
    CU_ASSERT(vec_size(vec) == 0);
    CU_ASSERT(vec_capacity(vec) == 1);

    CU_ASSERT(vec_pop_back(vec, &output) == DS_EMPTY_ERROR);

    vec_destroy(vec, NULL);
}

void testVecIterator(void) {
    vec_t* vec = vec_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output, i = 0;
    vec_push_back(vec, &a);
    vec_push_back(vec, &b);
    vec_push_back(vec, &c);
    vec_push_back(vec, &d);
    vec_push_back(vec, &e);

    ds_vec_iter_t* iter = vec_create_iter(vec);
    int expected[] = {47, 100, 101, 90, 1000};

    while (vec_iter_has_next(iter)) {
        get_vec_iter_data(iter, &output);
        CU_ASSERT(output == expected[i++]);
        vec_iter_next(iter);
    }

    vec_destroy_iter(iter);
    vec_destroy(vec, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite vec_queue = CU_add_suite("Vec Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(vec_queue, "Test for adding elements to a vec type", testVecElementAdd);
    CU_add_test(vec_queue, "Test for removing elements to a vec type", testVecElementRemove);
    CU_add_test(vec_queue, "Test Vec iterator", testVecIterator);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
