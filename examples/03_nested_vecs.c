#include <stdio.h>

// If this is not defined, then only headers will be generated
#define VECTOR_IMPLEMENTATION

// To see how vectors free one another
#define DEBUG

// === vec_int ===
#define VECTOR_ITEM_TYPE int
#include <vector.h>

// === vec_vec_int ===
#define VECTOR_ITEM_TYPE vec_int
#define VECTOR_ITEM_DESTRUCTOR vec_int_free
#include <vector.h>

// You can nest vectors all you want! If you want, you can create vec_vec_vec_vec_vec_.....

// === main code === 
int main() {
    vec_vec_int all_vectors = vec_vec_int_create();

    for (int i = 0; i < 5; i++) {
        vec_int vec = vec_int_create_copy((int[]){1 + i * 2, 2 + i * 2}, 2);
        vec_vec_int_push(all_vectors, vec);
    }

    for (int i = 0; i < all_vectors->length; i++) {
        for (int j = 0; j < all_vectors->data[i]->length; j++)
            printf("%d ", all_vectors->data[i]->data[j]);

        printf("\n");
    }

    // This function will free all the elements inside, no need to manually clean anything
    vec_vec_int_free(all_vectors);
}