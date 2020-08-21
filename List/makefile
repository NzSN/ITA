test: *.o
	g++ -g -o test $^ -lgtest -lgtest_main -lpthread
*.o: *.cpp
	g++ -c -g $^ -lgtest

do_test: test
	valgrind --leak-check=yes ./test
