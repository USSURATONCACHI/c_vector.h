#include <stdio.h>

// If this is not defined, then only headers will be generated
#define VECTOR_IMPLEMENTATION

#define VECTOR_ITEM_TYPE double
#include <vector.h>

int main() {
    vec_double vector = vec_double_create();

    vec_double_push(vector, 1.0);
    vec_double_push(vector, 2.0);
    vec_double_push(vector, 4.0);
    vec_double_push(vector, 5.0);
    vec_double_push(vector, 6.0);

    vec_double_insert(vector, 3.0, 2);

    for (int i = 0; i < vector->length; i++)
        printf("Element: %lf\n", vector->data[i]);

    while(vector->length > 0)
        printf("Pop: %lf\n", vec_double_popget(vector));

    vec_double_free(vector);
}