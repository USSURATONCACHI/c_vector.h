# Introduction
`vector.h` IS PURE C. 

`vector.h` is a header-only library that allows you to use vectors of whatever type you want (and nested vectors). Like template vectors from C++ but in C.

`vector.h` has no dependencies (except standard headers).

It is a simple analog to C++ templated `std::vector<T>` but in `PURE C`. It has all the basic features: 
* vectors can use any* type,
* is is really easy to create, use, and free nested vecs (example 03)
* vectors have all the basic functions,
* you can specify destructors (example 02),
* you can specify custom allocators (example 04),
* you can separate headers and implementations (example 05),
* you can make all functions static (example 06).

# Quick start

Check out examples for more information!
## Simple vector
```c
#include <stdio.h>

// Create your custom vector type like this:
#define VECTOR_IMPLEMENTATION   // Without this there will be only headers
#define VECTOR_ITEM_TYPE double
#include <vector.h>

int main() {
    vec_double vector = vec_double_create();

    vec_double_push(vector, 1.0);
    vec_double_push(vector, 2.0);
    vec_double_push(vector, 3.0);
    vec_double_insert(vector, 4.0, 1);

    // Extract last elements with _popget or destroy last elements with _popfree 
    double last = vec_double_popget(vector);
    printf("Pop: %lf\n", last);

    printf("4.0 = %lf\n", vector->data[1]);

    printf("length = %d, capacity = %d\n", vector->length, vector->capacity);

    vec_double_free(vector);
}
```

## Nested vectors
Check out example 03 for more info.
```c
#define VECTOR_IMPLEMENTATION

#define VECTOR_ITEM_TYPE double
#include <vector.h>
// === vec_double is available here ===

#define VECTOR_ITEM_TYPE vec_double
#define VECTOR_ITEM_DESTRUCTOR vec_double_free
#include <vector.h>
// === vec_vec_double is available here ===

int main() {
    vec_vec_double vectors = vec_vec_double_create();

    // do something...

    // This will also clean up all internal vectors, no need of for loops to clean
    vec_vec_double_free(vectors);
}

```

## Available functions
* `vec_T vec_T_create();` - create empty vector.
* `vec_T vec_T_create_copy(T* source, int length);` - create vector from data.
* `vec_T vec_T_from_raw(T* source, int length);` - cast pointer and length into vector.

* `void vec_T_push(vec_T vec, T item);` - push item to the very end of vector.
* `void vec_T_insert(vec_T vec, T item, int index);` - insert item at the index and shifts all other element to the right.

* `T vec_T_popget(vec_T vec);` - pop last element and return it.
* `void vec_T_popfree(vec_T vec);` - pop last element and destry it.

* `void vec_T_delete_fast(vec_T vec, int i);` - delete i-th element and replace it with last element.
* `void vec_T_delete_order(vec_T vec, int i);` - delete i-th element and shift all elements after to the left.

* `T vec_T_extract_fast(vec_T vec, int i);` - extract i-th element and replace it with last element.
* `T vec_T_extract_order(vec_T vec, int i);` - extract i-th element and shift all elements after to the left.

* `T vec_T_at(vec_T vec, int i);` - returns the i-th item (copies by value).
* `T* vec_T_atref(vec_T vec, int i);` - returns the pointer to i-th element.

# Examples

You can try examples for yourself by going to examples folder and using `make <test-name>` to run tests. Like this: `make 01_simple`.