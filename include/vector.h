/**
 * This header-only library allows to create template vectors in c.
 * Vectors can hold data with custom destructors. You can set VECTOR_ITEM_DESTRUCTOR to the destructor.
*/

// input macro: VECTOR_ITEM_TYPE - type
// input macro: VECTOR_ITEM_DESTRUCTOR - void function that accepts pointer to object, optional
// input macro: VECTOR_MALLOC_FN - function to allocate memory, optional
// input macro: VECTOR_FREE_FN - function to free memory, optional
// input macro: VECTOR_MAKE_STATIC - define to make all functions static
// input macro: DEBUG

#ifndef VECTOR_ITEM_TYPE
    #warning VECTOR_ITEM_TYPE is undefined, cannot construct vector.
#else
    #include <string.h>
    #ifndef VECTOR_MALLOC_FN 
        #include <stdlib.h>
        #define VECTOR_MALLOC_FN malloc
    #endif
    
    #ifndef VECTOR_FREE_FN 
        #include <stdlib.h>
        #define VECTOR_FREE_FN free
    #endif

    #ifdef VECTOR_MAKE_STATIC
        #define VEC_STATIC_PREFIX static
    #else  
        #define VEC_STATIC_PREFIX
    #endif
    #include <stddef.h>
    #define unreachable() __builtin_unreachable()

    #ifdef DEBUG 
        #include <stdio.h>
        #define panic(...) {\
            fprintf(stderr, "\n+-+-+-+-+-+-+-+-+-+-\n");\
            fprintf(stderr, "Panic in file %s, function %s, line %d: \n", __FILE__, __func__, __LINE__);\
            fprintf(stderr, __VA_ARGS__);\
            exit(-1);\
        }
    #endif

    #define CONCAT2(s1, s2) s1 ## s2
    #define CONCAT(s1, s2) CONCAT2(s1, s2)

    #define STR2(s) #s
    #define STR(s) STR2(s)

    #define VEC_T CONCAT(vec_, VECTOR_ITEM_TYPE)
    #define VEC_T_CONTENT CONCAT(VEC_T, _content)
    #define ITEM_T VECTOR_ITEM_TYPE
    #define VEC_DESTRUCTOR(_) VECTOR_ITEM_DESTRUCTOR



    typedef struct {
        VECTOR_ITEM_TYPE* data;
        int length;
        int capacity;
    } VEC_T_CONTENT;
    typedef VEC_T_CONTENT* VEC_T;


    // Names of functions
    #define VEC_CREATE(a)        CONCAT(VEC_T, _create)
    #define VEC_CREATE_COPY(a)   CONCAT(VEC_T, _create_copy)
    #define VEC_FROM_RAW(a)      CONCAT(VEC_T, _from_raw)

    #define VEC_PUSH(a)             CONCAT(VEC_T, _push)
    #define VEC_POPGET(a)           CONCAT(VEC_T, _popget)
    #define VEC_POPFREE(a)          CONCAT(VEC_T, _popfree)
    #define VEC_AT(a)               CONCAT(VEC_T, _at)
    #define VEC_ATREF(a)            CONCAT(VEC_T, _atref)
    #define VEC_EXTRACT_FAST(a)     CONCAT(VEC_T, _extract_fast)
    #define VEC_EXTRACT_ORDER(a)    CONCAT(VEC_T, _extract_order)
    #define VEC_DELETE_FAST(a)      CONCAT(VEC_T, _delete_fast)
    #define VEC_DELETE_ORDER(a)     CONCAT(VEC_T, _delete_order)
    
    #define VEC_FREE(a)     CONCAT(VEC_T, _free)


    // Function declarations
    VEC_STATIC_PREFIX VEC_T VEC_CREATE(_)           ();
    VEC_STATIC_PREFIX VEC_T VEC_CREATE_COPY(_)      (ITEM_T* source, int length);
    VEC_STATIC_PREFIX VEC_T VEC_FROM_RAW(_)         (ITEM_T* source, int length);
    
    VEC_STATIC_PREFIX void VEC_PUSH(_)              (VEC_T vec, ITEM_T item);

    VEC_STATIC_PREFIX ITEM_T VEC_POPGET(_)          (VEC_T vec);
    VEC_STATIC_PREFIX void VEC_POPFREE(_)           (VEC_T vec);

    VEC_STATIC_PREFIX ITEM_T VEC_AT(_)              (VEC_T vec, int i);
    VEC_STATIC_PREFIX ITEM_T* VEC_ATREF(_)          (VEC_T vec, int i);

    VEC_STATIC_PREFIX ITEM_T VEC_EXTRACT_FAST(_)    (VEC_T vec, int i);
    VEC_STATIC_PREFIX ITEM_T VEC_EXTRACT_ORDER(_)   (VEC_T vec, int i);
    VEC_STATIC_PREFIX void VEC_DELETE_FAST(_)       (VEC_T vec, int i);
    VEC_STATIC_PREFIX void VEC_DELETE_ORDER(_)      (VEC_T vec, int i);

    VEC_STATIC_PREFIX void VEC_FREE(_)  (VEC_T v);

    #ifdef VECTOR_IMPLEMENTATION
        // Implementations
        VEC_STATIC_PREFIX VEC_T VEC_CREATE() () {
            VEC_T ptr = (VEC_T) VECTOR_MALLOC_FN(sizeof(VEC_T_CONTENT));
            ptr->data = NULL;
            ptr->length = 0;
            ptr->capacity = 0;
            return ptr;
        }

        VEC_STATIC_PREFIX VEC_T VEC_CREATE_COPY(_)      (ITEM_T* source, int length) {
            VEC_T ptr = (VEC_T) VECTOR_MALLOC_FN(sizeof(VEC_T_CONTENT));
            ptr->data = (ITEM_T*) VECTOR_MALLOC_FN(sizeof(ITEM_T) * length);
            memcpy(ptr->data, source, length * sizeof(ITEM_T));

            ptr->length = length;
            ptr->capacity = length;
            return ptr;
        }

        VEC_STATIC_PREFIX VEC_T VEC_FROM_RAW(_)         (ITEM_T* source, int length) {
            VEC_T ptr = (VEC_T) VECTOR_MALLOC_FN(sizeof(VEC_T_CONTENT));
            ptr->data = source;
            ptr->length = length;
            ptr->capacity = length;
            return ptr;

        }

        VEC_STATIC_PREFIX void VEC_PUSH(_) (VEC_T vec, ITEM_T item) {
            if (vec->length > vec->capacity) {
                #ifdef DEBUG
                    panic("Absurd situation: vector length (%d) is bigger than it's capacity (%d)\n", vec->length, vec->capacity);
                #else
                    unreachable();
                #endif
            } else if (vec->length == vec->capacity) {
                int new_cap = vec->length * 3 / 2 + 4;
                ITEM_T* new_data = (ITEM_T*) VECTOR_MALLOC_FN(sizeof(ITEM_T) * new_cap);
                memcpy(new_data, vec->data, sizeof(ITEM_T) * vec->length);

                vec->data = new_data;
                vec->capacity = new_cap;
            }

            vec->data[vec->length] = item;
            vec->length++;
        }

        #ifdef DEBUG
            #define CHECK_LEN_ZERO(vec)\
                if (vec->length <= 0)\
                    panic("%s (at %p) is empty, it's length is %d\n", STR(VEC_T), (void*)vec, vec->length);

            #define CHECK_INDEX(vec, index)\
                if (index >= vec->length)\
                    panic("%s (at %p) index is out of bounds. Index = %d, length = %d\n", STR(VEC_T), (void*)vec, index, vec->length);
        #else
            #define CHECK_LEN_ZERO(vec) if (vec->length <= 0) unreachable();

            #define CHECK_INDEX(vec, index) if (index >= vec->length) unreachable();
        #endif

        VEC_STATIC_PREFIX ITEM_T VEC_POPGET(_) (VEC_T vec) {
            CHECK_LEN_ZERO(vec);
            vec->length--;
            return vec->data[vec->length];
        }

        VEC_STATIC_PREFIX void VEC_POPFREE(_) (VEC_T vec) {
            CHECK_LEN_ZERO(vec);
            vec->length--;

            #ifdef VECTOR_ITEM_DESTRUCTOR
                VEC_DESTRUCTOR(_) (vec->data[vec->length]);
            #endif
        }

        VEC_STATIC_PREFIX ITEM_T VEC_AT(_) (VEC_T vec, int i) {
            CHECK_INDEX(vec, i);
            return vec->data[i];
        }
        VEC_STATIC_PREFIX ITEM_T* VEC_ATREF(_) (VEC_T vec, int i) {
            CHECK_INDEX(vec, i);
            return &vec->data[i];
        }

        VEC_STATIC_PREFIX ITEM_T VEC_EXTRACT_FAST(_)    (VEC_T vec, int i) {
            CHECK_LEN_ZERO(vec);
            CHECK_INDEX(vec, i);

            ITEM_T item = vec->data[i];
            vec->data[i] = vec->data[vec->length - 1];
            vec->length--;
            return item;
        }

        VEC_STATIC_PREFIX ITEM_T VEC_EXTRACT_ORDER(_)   (VEC_T vec, int i) {
            CHECK_LEN_ZERO(vec);
            CHECK_INDEX(vec, i);

            ITEM_T item = vec->data[i];
            for (int index = i; i < vec->length - 1; i++)
                vec->data[index] = vec->data[index + 1];
            vec->length--;
            return item;
        }

        VEC_STATIC_PREFIX void VEC_DELETE_FAST(_)       (VEC_T vec, int i) {
            CHECK_LEN_ZERO(vec);
            CHECK_INDEX(vec, i);

            #ifdef VECTOR_ITEM_DESTRUCTOR
                VEC_DESTRUCTOR(_) (vec->data[i]);
            #endif
            vec->data[i] = vec->data[vec->length - 1];
            vec->length--;
        }
        VEC_STATIC_PREFIX void VEC_DELETE_ORDER(_)      (VEC_T vec, int i) {
            CHECK_LEN_ZERO(vec);
            CHECK_INDEX(vec, i);

            #ifdef VECTOR_ITEM_DESTRUCTOR
                VEC_DESTRUCTOR(_) (vec->data[i]);
            #endif

            for (int index = i; i < vec->length - 1; i++)
                vec->data[index] = vec->data[index + 1];

            vec->length--;
        }

        VEC_STATIC_PREFIX void VEC_FREE() (VEC_T v) {
            if (v == NULL)
                return;

            #ifdef VECTOR_ITEM_DESTRUCTOR
                for (int i = 0; i < v->length; i++) 
                    VEC_DESTRUCTOR(_) (v->data[i]);
            #endif

            if (v->data)
                VECTOR_FREE_FN(v->data);

            #ifdef DEBUG
                printf("Deleted " STR(VEC_T) " at %p (length %d)\n", (void*)v, v->length);
            #endif
            VECTOR_FREE_FN(v);
        }

    #endif

    #undef VECTOR_ITEM_TYPE
    #undef VECTOR_ITEM_DESTRUCTOR
    #undef VEC_T
    #undef ITEM_T
    #undef VEC_DESTRUCTOR
    #undef VEC_STATIC_PREFIX
    
    #undef VEC_CREATE
    #undef VEC_FREE
    #undef VEC_CREATE_COPY
    #undef VEC_FROM_RAW
    #undef VEC_PUSH
    #undef VEC_POPGET
    #undef VEC_POPFREE
    #undef VEC_AT
    #undef VEC_ATREF
    #undef VEC_EXTRACT_FAST
    #undef VEC_EXTRACT_ORDER
    #undef VEC_DELETE_FAST
    #undef VEC_DELETE_ORDER
    
#endif