#include <stdio.h>
#include <stdlib.h>

void* my_malloc(size_t size) {
    printf("Allocating %lld bytes!\n", size);
    return malloc(size);
}

void my_free(void* ptr) {
    printf("Freeing %p!\n", ptr);
    free(ptr);
}

#define VECTOR_IMPLEMENTATION
#define VECTOR_MALLOC_FN my_malloc
#define VECTOR_FREE_FN my_free

// === vec_int ===
#define VECTOR_ITEM_TYPE double
#include <vector.h>

// === main code === 
int main() {
    vec_double numbers = vec_double_create(); // Allocating the vector itself (pointer + int + int)

    vec_double_push(numbers, 1.0); // First allocation of data inside
    vec_double_push(numbers, 2.0);
    vec_double_push(numbers, 3.0);
    vec_double_push(numbers, 4.0);
    vec_double_push(numbers, 5.0); // Reallocation (expanding)

    vec_double_free(numbers);
}