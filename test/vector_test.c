#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "vector.h"

void testVecElementAdd(void) {
    ds_vector_t* vec = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, f = 10, g = 11, h = 808, output;
    vector_push_back(vec, &a);
    CU_ASSERT(vector_size(vec) == 1);
    CU_ASSERT(vector_capacity(vec) == 1);

    vector_push_back(vec, &b);
    CU_ASSERT(vector_size(vec) == 2);
    CU_ASSERT(vector_capacity(vec) == 2);

    vector_push_back(vec, &c);
    CU_ASSERT(vector_size(vec) == 3);
    CU_ASSERT(vector_capacity(vec) == 4);

    vector_push_back(vec, &d);
    CU_ASSERT(vector_size(vec) == 4);
    CU_ASSERT(vector_capacity(vec) == 4);

    vector_insert(vec, 0, &e);
    vector_front(vec, &output);
    CU_ASSERT(vector_size(vec) == 5);
    CU_ASSERT(vector_capacity(vec) == 8);
    CU_ASSERT(output == 1000);

    vector_insert(vec, 5, &f);
    vector_back(vec, &output);
    CU_ASSERT(vector_size(vec) == 6);
    CU_ASSERT(vector_capacity(vec) == 8);
    CU_ASSERT(output == 10);

    vector_insert(vec, 2, &g);
    vector_at(vec, 2, &output);
    CU_ASSERT(vector_size(vec) == 7);
    CU_ASSERT(vector_capacity(vec) == 8);
    CU_ASSERT(output == 11);

    CU_ASSERT(vector_insert(vec, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vector_at(vec, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vector_size(vec) == 7);
    CU_ASSERT(vector_capacity(vec) == 8);

    vector_destroy(vec, NULL);
}

void testVecElementRemove(void) {
    ds_vector_t* vec = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output;
    
    vector_push_back(vec, &a);
    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 47);
    CU_ASSERT(vector_size(vec) == 0);
    CU_ASSERT(vector_capacity(vec) == 1);


    vector_push_back(vec, &a);
    vector_push_back(vec, &b);
    vector_push_back(vec, &c);
    vector_push_back(vec, &d);
    vector_push_back(vec, &e);

    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 1000);
    CU_ASSERT(vector_size(vec) == 4);

    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 90);
    CU_ASSERT(vector_size(vec) == 3);

    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 101);
    CU_ASSERT(vector_size(vec) == 2);
    CU_ASSERT(vector_capacity(vec) == 4);

    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 100);
    CU_ASSERT(vector_size(vec) == 1);
    CU_ASSERT(vector_capacity(vec) == 2);

    vector_back(vec, &output);
    vector_pop_back(vec, NULL);
    CU_ASSERT(output == 47);
    CU_ASSERT(vector_size(vec) == 0);
    CU_ASSERT(vector_capacity(vec) == 1);

    CU_ASSERT(vector_pop_back(vec, NULL) == DS_EMPTY_ERROR);

    vector_destroy(vec, NULL);
}

void testVecIterator(void) {
    ds_vector_t* vec = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output, i = 0;
    vector_push_back(vec, &a);
    vector_push_back(vec, &b);
    vector_push_back(vec, &c);
    vector_push_back(vec, &d);
    vector_push_back(vec, &e);

    ds_vector_iter_t* iter = vector_create_iter(vec);
    int expected[] = {47, 100, 101, 90, 1000};

    while (vector_iter_has_next(iter)) {
        get_vector_iter_data(iter, &output);
        CU_ASSERT(output == expected[i++]);
        vector_iter_next(iter);
    }

    vector_destroy_iter(iter);
    vector_destroy(vec, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite vec_queue = CU_add_suite("Vector Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(vec_queue, "Test for adding elements to a vec type", testVecElementAdd);
    CU_add_test(vec_queue, "Test for removing elements to a vec type", testVecElementRemove);
    CU_add_test(vec_queue, "Test Vector iterator", testVecIterator);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failed = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failed > 0) ? 1 : 0;
}
