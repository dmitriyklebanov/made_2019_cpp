CC=g++
CFLAGS=-c -Wall -std=c++14

all: test_compile

test: test_compile
	./deserializer_test
	./serializer_test
	./combined_test

test_compile: deserializer_test_compile serializer_test_compile combined_test_compile

deserializer_test_compile: deserializer_test.o
	$(CC) -o deserializer_test deserializer_test.o
	
deserializer_test.o: deserializer.h errors.hpp tester.hpp testlib.hpp
	$(CC) $(CFLAGS) deserializer_test.cpp
	
serializer_test_compile: serializer_test.o
	$(CC) -o serializer_test serializer_test.o
	
serializer_test.o: errors.hpp serializer.h tester.hpp testlib.hpp
	$(CC) $(CFLAGS) serializer_test.cpp
	
combined_test_compile: combined_test.o
	$(CC) -o combined_test combined_test.o
	
combined_test.o: deserializer.h errors.hpp serializer.h testlib.hpp
	$(CC) $(CFLAGS) combined_test.cpp
	
clean:
	rm -rf *.o deserializer_test serializer_test combined_test
