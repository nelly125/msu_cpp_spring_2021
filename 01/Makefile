CC=g++ --std=c++17

WARNINGS= -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

FLAGS= -O3 -ffast-math -g -fsanitize=address

all: test clear run

test: main.o
	$(CC) $(FLAGS) $(WARNINGS) -o test main.o -lm

main.o:
	$(CC) $(FLAGS) $(WARNINGS) -c main.cpp

run: test
	./test

clear:
	rm -rf *.o