CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile perf_test_compile

test: test_compile
	./test

test_compile: test.o allocator.o
	$(CC) -o test test.o allocator.o

test.o: test.cpp tester.hpp allocator.h
	$(CC) $(CFLAGS) test.cpp

perf_test: perf_test_compile
	./perf_test

perf_test_compile: perf_test.o timer.o allocator.o
	$(CC) -o perf_test perf_test.o timer.o allocator.o

perf_test.o: perf_test.cpp timer.h tester.hpp allocator.h
	$(CC) $(CFLAGS) perf_test.cpp

timer.o: timer.cpp timer.h
	$(CC) $(CFLAGS) timer.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(CFLAGS) allocator.cpp

clean:
	rm -rf *.o test perf_test
