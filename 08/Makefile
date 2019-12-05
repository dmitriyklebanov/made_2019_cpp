CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./vector_test

test_compile: vector_test_compile

vector_test_compile: vector_test.o
	$(CC) -o vector_test vector_test.o
	
vector_test.o: vector.hpp vector_test.cpp
	$(CC) $(CFLAGS) vector_test.cpp

clean:
	rm -rf *.o vector_test
