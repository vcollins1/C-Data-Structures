cmake_minimum_required(VERSION 3.21)
project(CDataStructures LANGUAGES C)

add_library(data_structures
    src/list.c
    src/vector.c
    src/stack.c
    src/queue.c
)
target_compile_features(data_structures PRIVATE c_std_17)
target_include_directories(data_structures PUBLIC include)

find_path(CUNIT_INCLUDE_DIR CUnit/Basic.h)
find_library(CUNIT_LIBRARY cunit)

if(NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
    message(FATAL_ERROR "CUnit not found")
endif()

add_executable(list_test test/list_test.c)
target_include_directories(list_test PRIVATE ${CUNIT_INCLUDE_DIR})
target_compile_features(list_test PRIVATE c_std_17)
target_compile_options(list_test PRIVATE -g -Wall -Wextra -Wpedantic)
target_link_libraries(list_test
    PRIVATE
        ${CUNIT_LIBRARY}
        data_structures
)

add_executable(vector_test test/vector_test.c)
target_include_directories(vector_test PRIVATE ${CUNIT_INCLUDE_DIR})
target_compile_features(vector_test PRIVATE c_std_17)
target_compile_options(vector_test PRIVATE -g -Wall -Wextra -Wpedantic)
target_link_libraries(vector_test
    PRIVATE
        ${CUNIT_LIBRARY}
        data_structures
)

add_executable(stack_test test/stack_test.c)
target_include_directories(stack_test PRIVATE ${CUNIT_INCLUDE_DIR})
target_compile_features(stack_test PRIVATE c_std_17)
target_compile_options(stack_test PRIVATE -g -Wall -Wextra -Wpedantic)
target_link_libraries(stack_test
    PRIVATE
        ${CUNIT_LIBRARY}
        data_structures
)

add_executable(queue_test test/queue_test.c)
target_include_directories(queue_test PRIVATE ${CUNIT_INCLUDE_DIR})
target_compile_features(stack_test PRIVATE c_std_17)
target_compile_options(stack_test PRIVATE -g -Wall -Wextra -Wpedantic)
target_link_libraries(queue_test
    PRIVATE
        ${CUNIT_LIBRARY}
        data_structures
)