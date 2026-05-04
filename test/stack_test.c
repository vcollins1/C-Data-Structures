#include <CUnit/Basic.h>
#include <err.h>
#include <stdlib.h>
#include "stack.h"

void test_stack_push(void) {
    stackDS_t* stack = stack_create(sizeof(int));
    int a = 10, b = 20, c = 30, d = 90, e = 100, f = 110, output;
    
    stack_push(stack, &a);
    stack_top(stack, &output);
    CU_ASSERT(output == 10);

    stack_push(stack, &b);
    stack_top(stack, &output);
    CU_ASSERT(output == 20);

    stack_push(stack, &c);
    stack_top(stack, &output);
    CU_ASSERT(output == 30);

    stack_push(stack, &d);
    stack_top(stack, &output);
    CU_ASSERT(output == 90);

    stack_push(stack, &e);
    stack_top(stack, &output);
    CU_ASSERT(output == 100);

    stack_push(stack, &f);
    stack_top(stack, &output);
    CU_ASSERT(output == 110);

    CU_ASSERT(stack_size(stack) == 6);

    stack_destroy(stack, NULL);
}

void test_stack_pop(void) {
    stackDS_t* stack = stack_create(sizeof(int));
    int a = 10, b = 20, c = 30, d = 90, e = 100, f = 110;
    
    stack_push(stack, &a);
    stack_push(stack, &b);
    stack_push(stack, &c);
    stack_push(stack, &d);
    stack_push(stack, &e);
    stack_push(stack, &f);

    stack_pop(stack);
    CU_ASSERT(stack_size(stack) == 5);
    stack_pop(stack);
    CU_ASSERT(stack_size(stack) == 4);
    stack_pop(stack);
    CU_ASSERT(stack_size(stack) == 3);
    stack_pop(stack);
    CU_ASSERT(stack_size(stack) == 2);
    stack_pop(stack);
    CU_ASSERT(stack_size(stack) == 1);
    stack_pop(stack);
    CU_ASSERT(stack_empty(stack));

    stack_destroy(stack, NULL);
}


int main(void) {
    if (CU_initialize_registry() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "can't initialize test registry");

    CU_pSuite suite_stack = CU_add_suite("Vec Test Suite", NULL, NULL);
    if (CU_get_error() != CUE_SUCCESS)
        errx(EXIT_FAILURE, "%s", CU_get_error_msg());

    CU_add_test(suite_stack, "Test for pushing to the stack", test_stack_push);
    CU_add_test(suite_stack, "Test for popping the stack", test_stack_pop);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
