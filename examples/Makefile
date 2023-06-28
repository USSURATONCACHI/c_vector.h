CC=gcc -Wall -Wextra -Wpedantic -O3 -I../include

# OS - dependent
RMRF=rm -rf
EXEC_EXT=

ifeq ($(OS),Windows_NT)
	RMRF=../sane_rm.exe
	EXEC_EXT=exe
endif

all: 01_simple 02_destructor 03_nested_vecs 04_custom_allocator 05_distinct_headers 06_static_funcs


01_simple: 01_simple.${EXEC_EXT}
	./$<
01_simple.${EXEC_EXT}: 01_simple.c ../include/vector.h
	${CC} $< -o $@


02_destructor: 02_destructor.${EXEC_EXT}
	./$<
02_destructor.${EXEC_EXT}: 02_destructor.c ../include/vector.h
	${CC} $< -o $@


03_nested_vecs: 03_nested_vecs.${EXEC_EXT}
	./$<
03_nested_vecs.${EXEC_EXT}: 03_nested_vecs.c ../include/vector.h
	${CC} $< -o $@


04_custom_allocator: 04_custom_allocator.${EXEC_EXT}
	./$<
04_custom_allocator.${EXEC_EXT}: 04_custom_allocator.c ../include/vector.h
	${CC} $< -o $@


05_distinct_headers: 05_distinct_headers.${EXEC_EXT}
	./$<
05_distinct_headers.${EXEC_EXT}: 05_distinct_headers.c 05_vectors.c 05_vectors.h ../include/vector.h
	${CC} -c 05_vectors.c -o 05_vectors.o
	${CC} -c 05_distinct_headers.c -o 05_distinct_headers.o
	${CC} 05_vectors.o 05_distinct_headers.o -o $@


06_static_funcs: 06_static_funcs.${EXEC_EXT}
	./$<
06_static_funcs.${EXEC_EXT}: 06_static_funcs.c 06_vector_copy.c ../include/vector.h
	${CC} -c 06_static_funcs.c -o 06_static_funcs.o
	${CC} -c 06_vector_copy.c -o 06_vector_copy.o
	${CC} 06_static_funcs.o 06_vector_copy.o -o $@

clean:
	${RMRF} *${EXEC_EXT}
	${RMRF} *.o