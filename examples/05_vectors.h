#ifndef EXAMPLES_05_VECTORS_H_
#define EXAMPLES_05_VECTORS_H_

#undef VECTOR_IMPLEMENTATION // Only headers

#define VECTOR_ITEM_TYPE int
#include <vector.h>

#define VECTOR_ITEM_TYPE double
#include <vector.h>

typedef char* string_t;

#define VECTOR_ITEM_TYPE string_t
#include <vector.h>

#endif // EXAMPLES_05_VECTORS_H_