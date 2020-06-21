GCC = gcc
FLAGS = -Wall -std=c99 # consider c89?
EXEC = out

# -O2?
build: *.c
	$(GCC) $(FLAGS) $^ -lm -o $(EXEC)

run: build
	./$(EXEC)

clean: $(EXEC)
	rm -rf $^
