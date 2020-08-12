all:

test: heapSort.o quickSort.o
	g++ -std=c++2a -o test test.cpp heapSort.o quickSort.o -lgtest -lpthread
heapSort.o: heapSort.cpp
	g++ -g -c -std=c++2a -o heapSort.o heapSort.cpp

quickSort.o: quickSort.cpp
	g++ -g -c -std=c++2a -o quickSort.o quickSort.cpp

do_test: test
	valgrind --leak-check=yes ./test

clean:
	rm quickSort.o heapSort.o test
