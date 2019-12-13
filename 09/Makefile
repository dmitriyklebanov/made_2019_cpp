CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./thread_pool_test

test_compile: thread_pool_test_compile

thread_pool_test_compile: thread_pool_test.o
	$(CC) -o thread_pool_test -pthread thread_pool_test.o
	
thread_pool_test.o: thread_pool.hpp thread_pool_test.cpp
	$(CC) $(CFLAGS) thread_pool_test.cpp

clean:
	rm -rf *.o thread_pool_test
