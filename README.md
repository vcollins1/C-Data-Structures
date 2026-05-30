# C Data Structures

A small C17 data-structures library with generic containers, callback-based cleanup,
and CUnit tests. The containers store copies of user-provided values, so callers can
work with stack variables while the data structure owns its internal element memory.

## Implemented Structures

| Structure | Header             | Backing implementation | Highlights                                                           |
|-----------|--------------------|------------------------|----------------------------------------------------------------------|
| List      | `include/list.h`   | Linked list            | Front/back insert and removal, indexed access, search, set, iterator |
| Vector    | `include/vector.h` | Dynamic array          | Push, insert, pop, indexed access, capacity growth/shrink, iterator  |
| Stack     | `include/stack.h`  | Vector                 | Push, pop, top                                                       |
| Queue     | `include/queue.h`  | List                   | Enqueue, dequeue, front                                              |
| Deque     | `include/deque.h`  | List                   | Push/pop at both ends, front/back access                             |

Shared status codes and callback types are defined in `include/ds_utils.h`.

## Project Layout

```text
.
|-- include/        Public headers
|-- src/            Data-structure implementations
|-- test/           CUnit test programs
|-- CMakeLists.txt  Build and test configuration
`-- main.c          Small standalone demo entry point
```

## Requirements

- A C17-compatible compiler
- CMake 3.21 or newer
- CUnit development headers and library

On macOS with Homebrew:

```sh
brew install cmake cunit
```

On Debian/Ubuntu:

```sh
sudo apt install cmake libcunit1-dev
```

## Build

Configure and build out of tree:

```sh
cmake -S . -B build
cmake --build build
```

The build creates the `data_structures` library plus one executable per test suite:

- `list_test`
- `vector_test`
- `stack_test`
- `queue_test`
- `deque_test`

## Run Tests

Run all tests through CTest:

```sh
ctest --test-dir build --output-on-failure
```

Or run an individual test executable directly:

```sh
./build/vector_test
```

## Usage Example

```c
#include <stdio.h>
#include "vector.h"

int main(void) {
    ds_vector_t* numbers = vector_create(sizeof(int));
    if (!numbers) {
        return 1;
    }

    int value = 42;
    if (vector_push_back(numbers, &value) != DS_SUCCESS_OK) {
        vector_destroy(numbers, NULL);
        return 1;
    }

    int output = 0;
    if (vector_back(numbers, &output) == DS_SUCCESS_OK) {
        printf("%d\n", output);
    }

    vector_destroy(numbers, NULL);
    return 0;
}
```

Each container receives the element size at creation time and copies bytes from the
`void*` value passed into insertion functions. Access functions copy the stored value
into caller-owned output memory.

## Memory Management

Container nodes and stored element buffers are managed by the library. If the stored
values own additional resources, pass a `clear_callback` to removal, clear, or destroy
functions so each element can release its nested memory before the container frees the
element buffer.

For plain values such as `int`, `double`, or small structs with no owned pointers,
use `NULL` as the cleanup callback:

```c
vector_destroy(numbers, NULL);
```

For pointer-owning values, provide a cleanup callback:

```c
static void free_string(void* data) {
    char** value = data;
    free(*value);
}

vector_destroy(strings, free_string);
```

## Status Codes

Most mutating and access functions return a `ds_status_code_t`:

- `DS_SUCCESS_OK`
- `DS_REMOVE_ERROR`
- `DS_MEMORY_ERROR`
- `DS_INDEX_ERROR`
- `DS_EMPTY_ERROR`
- `DS_NULL_ERROR`
- `DS_ELEMENT_NOT_FOUND`

Check return values before using output data, especially for indexed access, removal,
and operations on containers that may be empty.

## Development Notes

The project is compiled with strict warnings enabled:

```cmake
-g -Wall -Wextra -Wpedantic -Werror
```

When adding a new container or feature, add tests under `test/` and register the test
target in `CMakeLists.txt` so it runs through CTest.
