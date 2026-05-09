#include <CUnit/Basic.h>
#include <stdlib.h>
#include <err.h>
#include "deque.h"

void test_deque_inserts(void) {
    ds_deque_t* deque = deque_create(sizeof(int));
    int input, output;

    input = 47;
    deque_push_front(deque, &input);
    CU_ASSERT(deque_size(deque) == 1);

    input = 100;
    deque_push_back(deque, &input);
    CU_ASSERT(deque_size(deque) == 1);

    deque_front(deque, &output);
    CU_ASSERT(output == 47);

    deque_back(deque, &output);
    CU_ASSERT(output == 100);

    deque_destroy(deque, NULL);
}

void test_deque_removes(void) {
    ds_deque_t* deque = deque_create(sizeof(int));
    int input;

    input = 47;
    deque_push_front(deque, &input);

    input = 100;
    deque_push_back(deque, &input);
    CU_ASSERT(deque_size(deque) == 2);

    deque_pop_front(deque, NULL);
    CU_ASSERT(deque_size(deque) == 1);

    deque_pop_back(deque, NULL);
    CU_ASSERT(deque_empty(deque) == true);

    deque_destroy(deque, NULL);
}


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize the registry");

    CU_pSuite deque_suite = CU_add_suite("Deque test suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(deque_suite, "deque insert test", test_deque_inserts);
    CU_add_test(deque_suite, "deque removes test", test_deque_removes);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failed = CU_get_number_of_tests_failed();

    CU_cleanup_registry();
    return (failed > 0) ? 1 : 0;
}
