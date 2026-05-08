#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "queue.h"

void test_enqueue(void) {
    ds_queue_t* queue = queue_create(sizeof(int));
    int a = 10, b = 20, c = 30;
    
    queue_enqueue(queue, &a);
    CU_ASSERT(queue_size(queue) == 1);

    queue_enqueue(queue, &b);
    CU_ASSERT(queue_size(queue) == 2);

    queue_enqueue(queue, &c);
    CU_ASSERT(queue_size(queue) == 3);

    queue_destroy(queue, NULL);
}

void test_dequeue(void) {
    ds_queue_t* queue = queue_create(sizeof(int));
    int a = 10, b = 20, c = 30, output;
    
    queue_enqueue(queue, &a);
    queue_enqueue(queue, &b);
    queue_enqueue(queue, &c);

    queue_front(queue, &output);
    queue_dequeue(queue, NULL);
    CU_ASSERT(output == 10);

    queue_front(queue, &output);
    queue_dequeue(queue, NULL);
    CU_ASSERT(output == 20);

    queue_front(queue, &output);
    queue_dequeue(queue, NULL);
    CU_ASSERT(output == 30);

    CU_ASSERT(queue_empty(queue));

    queue_destroy(queue, NULL);
}


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite queue_suite = CU_add_suite("Queue Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(queue_suite, "Test for enqueue", test_enqueue);
    CU_add_test(queue_suite, "Test for dequeue", test_dequeue);
    
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    unsigned int failed = CU_get_number_of_tests_failed();
    CU_cleanup_registry();
    return (failed > 0) ? 1 : 0;
}
