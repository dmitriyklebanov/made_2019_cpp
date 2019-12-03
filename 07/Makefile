CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./format_test

test_compile: format_test_compile

format_test_compile: format_test.o
	$(CC) -o format_test format_test.o
	
bigint_test.o: format.hpp tester.hpp
	$(CC) $(CFLAGS) format_test.cpp
	
clean:
	rm -rf *.o format_test
