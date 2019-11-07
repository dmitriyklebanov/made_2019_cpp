CC=g++
CFLAGS=-c -Wall -std=c++14

all: run_compile test_compile

run: run_compile
	./run "$(ARGS)"

run_compile: run.o parser.o
	$(CC) -o run run.o parser.o

run.o: run.cpp parser.h
	$(CC) $(CFLAGS) run.cpp

test: test_compile
	./test

test_compile: test.o parser.o
	$(CC) -o test test.o parser.o

test.o: test.cpp tester.hpp parser.h
	$(CC) $(CFLAGS) test.cpp

parser.o: parser.cpp parser.h
	$(CC) $(CFLAGS) parser.cpp

clean:
	rm -rf *.o run test
