CC=g++ --std=c++17

WARNINGS= -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

FLAGS= -fsanitize=address

all: prog clean
test: run

prog: main.o Allocator.o
	$(CC) $(FLAGS) $(WARNINGS) -o prog main.o Allocator.o -lm

main.o:
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

Allocator.o: Allocator.cpp
	$(CC) $(FLAGS) $(WARNINGS) -c Allocator.cpp

.PHONY: clean

clean:
	rm -rf *.o

run:
	./prog