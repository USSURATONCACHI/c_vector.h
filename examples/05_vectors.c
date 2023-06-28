#include <stdlib.h>

#define VECTOR_IMPLEMENTATION

#define VECTOR_ITEM_TYPE int
#include <vector.h>

#define VECTOR_ITEM_TYPE double
#include <vector.h>



typedef char* string_t;
void string_free(char* ptr) {
    free(ptr);
}

#define VECTOR_ITEM_TYPE string_t
#define VECTOR_ITEM_DESTRUCTOR string_free
#include <vector.h>