CC=g++
CFLAGS=-c -Wall -std=c++14

all: run_compile test_compile

run: run_compile
	./run "$(ARGS)"

run_compile: run.o expression.o
	$(CC) -o run run.o expression.o

run.o: run.cpp expression.h
	$(CC) $(CFLAGS) run.cpp

test: test_compile
	./test

test_compile: test.o expression.o
	$(CC) -o test test.o expression.o

test.o: test.cpp tester.hpp expression.h
	$(CC) $(CFLAGS) test.cpp

expression.o: expression.cpp expression.h
	$(CC) $(CFLAGS) expression.cpp

clean:
	rm -rf *.o run test
