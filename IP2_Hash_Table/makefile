CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -c -Wno-self-assign-overloaded -Wno-unused-variable

TEST = Test
DEMO = Demo

TEST_LOG = log.txt

demo.o: demo.cpp realizacija.h
	$(CC) $(CFLAGS) demo.cpp -o demo.o

realizacija.o: realizacijaBroken.cpp realizacija.h
	$(CC) $(CFLAGS) realizacijaBroken.cpp -o realizacija.o

test.o: test.cpp realizacija.h
	$(CC) $(CFLAGS) test.cpp -o test.o

demo: demo.o realizacija.o
	$(CC) realizacija.o demo.o -o $(DEMO)

test: test.o realizacija.o
	$(CC) realizacija.o test.o -o $(TEST)


run_demo: demo
	./$(DEMO)

run_test: test
	./$(TEST) > $(TEST_LOG)	2>&1

all:
	$(MAKE) demo
	$(MAKE) test

clean:
	rm *.o $(TEST) $(DEMO)

rebuild:
	$(MAKE) clean
	$(MAKE) all
