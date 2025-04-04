demo: demo.o realizacija.o
	g++ realizacija.o demo.o -o demo

test: test.o realizacija.o
	g++ realizacija.o test.o -o test

demo.o: demo.cpp header.h
	g++ -c demo.cpp -o demo.o

stack.o: realizacija.cpp header.h
	g++ -c realizacija.cpp -o realizacija.o

test.o: test.cpp header.h
	g++ -c test.cpp -o test.o

run_demo: demo
	./demo

run_test: test
	./test

clean:
	rm *.o program *.txt
	clear