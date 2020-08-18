all:

test: heapSort.o quickSort.o mergeSort.o countingSort.o
	g++ -g -std=c++2a -o test test.cpp heapSort.o quickSort.o mergeSort.o countingSort.o -lgtest -lpthread

countingSort.o: countingSort.cpp
	g++ -g -c -std=c++2a -o countingSort.o countingSort.cpp

heapSort.o: heapSort.cpp
	g++ -g -c -std=c++2a -o heapSort.o heapSort.cpp

quickSort.o: quickSort.cpp
	g++ -g -c -std=c++2a -o quickSort.o quickSort.cpp

mergeSort.o: mergeSorts.cpp
	g++ -g -c -std=c++2a -o mergeSort.o mergeSorts.cpp

do_test: test
	valgrind --leak-check=yes ./test

clean:
	rm quickSort.o heapSort.o mergeSort.o test
