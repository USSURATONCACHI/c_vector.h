#include <stdio.h>

#include "05_vectors.h"

int main() {
    vec_int vec1 = vec_int_create();
    vec_double vec2 = vec_double_create();
    vec_string_t vec3 = vec_string_t_create();

    printf("Check 05_distinct_headers.o and 05_vectors.o with nm to see symbols!\n");
    printf("All the vector symbols are in 05_vectors.o\n");

    vec_string_t_free(vec3);
    vec_double_free(vec2);
    vec_int_free(vec1);
}