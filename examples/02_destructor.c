#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// We need one-token-name to be able to make vector
typedef char* char_ptr;

void string_free(char* ptr) {
    printf("Freeing string `%s`\n", ptr);
    free(ptr);
}

char* string_create(const char* source) {
    int length = strlen(source) + 1;
    char* result = (char*) malloc(sizeof(char) * length);
    strcpy(result, source);
    return result;
}

// If this is not defined, then only headers will be generated
#define VECTOR_IMPLEMENTATION

// === vec_char_ptr ===
#define VECTOR_ITEM_TYPE char_ptr
#define VECTOR_ITEM_DESTRUCTOR string_free
#include <vector.h>
// === vec_char_ptr ===

int main() {
    vec_char_ptr vector = vec_char_ptr_create();

    vec_char_ptr_push(vector, string_create("All"));
    vec_char_ptr_push(vector, string_create("Your"));
    vec_char_ptr_push(vector, string_create("Codebase"));
    vec_char_ptr_push(vector, string_create("Belongs"));
    vec_char_ptr_push(vector, string_create("To"));
    vec_char_ptr_push(vector, string_create("Us"));

    for (int i = 0; i < vector->length; i++)
        printf("Element: %s\n", vector->data[i]);

    // This function will free all the elements inside, no need to manually clean anything
    vec_char_ptr_free(vector);
}