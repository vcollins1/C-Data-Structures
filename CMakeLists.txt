cmake_minimum_required(VERSION 3.21)
project(CDataStructures LANGUAGES C)

set(CFLAGS -g -Wall -Wextra -Wpedantic -Werror -fPIC)
set(TEST_TARGETS list_test vector_test stack_test queue_test deque_test)

add_library(data_structures SHARED
    src/list.c
    src/vector.c
    src/stack.c
    src/queue.c
    src/deque.c
    src/int_list.c
)
target_compile_features(data_structures PRIVATE c_std_17)
target_compile_options(data_structures PRIVATE ${CFLAGS})
target_include_directories(data_structures PUBLIC include)

find_path(CUNIT_INCLUDE_DIR CUnit/Basic.h)
find_library(CUNIT_LIBRARY cunit)

if(NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
    message(FATAL_ERROR "CUnit not found")
endif()

foreach(TEST ${TEST_TARGETS})
    add_executable(${TEST} test/${TEST}.c)
    target_include_directories(${TEST} PRIVATE ${CUNIT_INCLUDE_DIR})
    target_compile_features(${TEST} PRIVATE c_std_17)
    target_compile_options(${TEST} PRIVATE ${CFLAGS})
    target_link_libraries(${TEST}
        PRIVATE
            ${CUNIT_LIBRARY}
            data_structures
    )
    add_test(NAME ${TEST} COMMAND ${TEST})
endforeach()

enable_testing()
