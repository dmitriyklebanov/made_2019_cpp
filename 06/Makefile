CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./bigint_test

test_compile: bigint_test_compile

bigint_test_compile: bigint_test.o bigint.o
	$(CC) -o bigint_test bigint_test.o bigint.o
	
bigint_test.o: bigint.h tester.hpp bigint_test.cpp
	$(CC) $(CFLAGS) bigint_test.cpp

bigint.o: bigint.h bigint.cpp utils/vector.hpp
	$(CC) $(CFLAGS) bigint.cpp
	
clean:
	rm -rf *.o bigint_test
