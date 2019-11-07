CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./test

test_compile: test.o matrix.o
	$(CC) -o test test.o matrix.o

test.o: test.cpp tester.hpp matrix.h
	$(CC) $(CFLAGS) test.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) $(CFLAGS) matrix.cpp

clean:
	rm -rf *.o test
