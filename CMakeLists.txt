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

set(TEST_TARGETS list_test vector_test stack_test queue_test)

find_path(CUNIT_INCLUDE_DIR CUnit/Basic.h)
find_library(CUNIT_LIBRARY cunit)

if(NOT CUNIT_INCLUDE_DIR OR NOT CUNIT_LIBRARY)
    message(FATAL_ERROR "CUnit not found")
endif()

foreach(TEST ${TEST_TARGETS})
    add_executable(${TEST} test/${TEST}.c)
    target_include_directories(${TEST} PRIVATE ${CUNIT_INCLUDE_DIR})
    target_compile_features(${TEST} PRIVATE c_std_17)
    target_compile_options(${TEST} PRIVATE -g -Wall -Wextra -Wpedantic)
    target_link_libraries(${TEST}
        PRIVATE
            ${CUNIT_LIBRARY}
            data_structures
    )
endforeach()
