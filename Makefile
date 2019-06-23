GCC = gcc

build: *.c
	$(GCC) $^ -o out
