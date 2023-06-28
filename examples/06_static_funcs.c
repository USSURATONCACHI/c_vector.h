// Disable warning
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"

#include <stdio.h>

#define VECTOR_IMPLEMENTATION
#define VECTOR_ITEM_TYPE int
#include <vector.h>

int main() {
    // We can use same symbols in two different 
    // files by making them static
    printf("It runs, success!");
}

#pragma GCC diagnostic pop