#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "vector.h"

void testVectorElementAdd(void) {
    ds_vector_t* vector = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, f = 10, g = 11, h = 808, output;
    vector_push_back(vector, &a);
    CU_ASSERT(vector_size(vector) == 1);
    CU_ASSERT(vector_capacity(vector) == 1);

    vector_push_back(vector, &b);
    CU_ASSERT(vector_size(vector) == 2);
    CU_ASSERT(vector_capacity(vector) == 2);

    vector_push_back(vector, &c);
    CU_ASSERT(vector_size(vector) == 3);
    CU_ASSERT(vector_capacity(vector) == 4);

    vector_push_back(vector, &d);
    CU_ASSERT(vector_size(vector) == 4);
    CU_ASSERT(vector_capacity(vector) == 4);

    vector_insert(vector, 0, &e);
    vector_front(vector, &output);
    CU_ASSERT(vector_size(vector) == 5);
    CU_ASSERT(vector_capacity(vector) == 8);
    CU_ASSERT(output == 1000);

    vector_insert(vector, 5, &f);
    vector_back(vector, &output);
    CU_ASSERT(vector_size(vector) == 6);
    CU_ASSERT(vector_capacity(vector) == 8);
    CU_ASSERT(output == 10);

    vector_insert(vector, 2, &g);
    vector_at(vector, 2, &output);
    CU_ASSERT(vector_size(vector) == 7);
    CU_ASSERT(vector_capacity(vector) == 8);
    CU_ASSERT(output == 11);

    CU_ASSERT(vector_insert(vector, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vector_at(vector, 8, &h) == DS_INDEX_ERROR);
    CU_ASSERT(vector_size(vector) == 7);
    CU_ASSERT(vector_capacity(vector) == 8);

    vector_destroy(vector, NULL);
}

void testVectorElementRemove(void) {
    ds_vector_t* vector = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output;
    
    vector_push_back(vector, &a);
    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 47);
    CU_ASSERT(vector_size(vector) == 0);
    CU_ASSERT(vector_capacity(vector) == 1);


    vector_push_back(vector, &a);
    vector_push_back(vector, &b);
    vector_push_back(vector, &c);
    vector_push_back(vector, &d);
    vector_push_back(vector, &e);

    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 1000);
    CU_ASSERT(vector_size(vector) == 4);

    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 90);
    CU_ASSERT(vector_size(vector) == 3);

    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 101);
    CU_ASSERT(vector_size(vector) == 2);
    CU_ASSERT(vector_capacity(vector) == 4);

    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 100);
    CU_ASSERT(vector_size(vector) == 1);
    CU_ASSERT(vector_capacity(vector) == 2);

    vector_back(vector, &output);
    vector_pop_back(vector, NULL);
    CU_ASSERT(output == 47);
    CU_ASSERT(vector_size(vector) == 0);
    CU_ASSERT(vector_capacity(vector) == 1);

    CU_ASSERT(vector_pop_back(vector, NULL) == DS_EMPTY_ERROR);

    vector_destroy(vector, NULL);
}

void testVectorIterator(void) {
    ds_vector_t* vector = vector_create(sizeof(int));
    int a = 47, b = 100, c = 101, d = 90, e = 1000, output, i = 0;
    vector_push_back(vector, &a);
    vector_push_back(vector, &b);
    vector_push_back(vector, &c);
    vector_push_back(vector, &d);
    vector_push_back(vector, &e);

    ds_vector_iter_t* iter = vector_create_iter(vector);
    int expected[] = {47, 100, 101, 90, 1000};

    while (vector_iter_has_next(iter)) {
        get_vector_iter_data(iter, &output);
        CU_ASSERT(output == expected[i++]);
        vector_iter_next(iter);
    }

    vector_destroy_iter(iter);
    vector_destroy(vector, NULL);
}

int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite vector_suite = CU_add_suite("Vector Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(vector_suite, "Test for adding elements to a vector type", testVectorElementAdd);
    CU_add_test(vector_suite, "Test for removing elements from a vector type", testVectorElementRemove);
    CU_add_test(vector_suite, "Test Vector iterator", testVectorIterator);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failed = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failed > 0) ? 1 : 0;
}
