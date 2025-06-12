CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -c -Wno-self-assign-overloaded -Wno-unused-variable

COMPARE = CompareByLength.o CompareByTitle.o CompareByArtist.o
SORT = TreeSort.o GnomeSort.o
HEADER = Song.h SongPlaylist.h SortingAlgorithm.h CompareStrategy.h CompareByArtist.h

TEST = Test
DEMO = Demo

TEST_LOG = log.txt

demo.o: demo.cpp $(HEADER)
	$(CC) $(CFLAGS) demo.cpp -o demo.o

test.o: test.cpp $(HEADER)
	$(CC) $(CFLAGS) test.cpp -o test.o

CompareByLength.o: CompareByLength.cpp $(HEADER)
	$(CC) $(CFLAGS) CompareByLength.cpp -o CompareByLength.o

CompareByTitle.o: CompareByTitle.cpp $(HEADER)
	$(CC) $(CFLAGS) CompareByTitle.cpp -o CompareByTitle.o

CompareByArtist.o: CompareByArtist.cpp $(HEADER)
	$(CC) $(CFLAGS) CompareByArtist.cpp -o CompareByArtist.o

TreeSort.o: TreeSort.cpp $(HEADER)
	$(CC) $(CFLAGS) TreeSort.cpp -o TreeSort.o

GnomeSort.o: GnomeSort.cpp $(HEADER)
	$(CC) $(CFLAGS) GnomeSort.cpp -o GnomeSort.o

Song.o: Song.cpp Song.h
	$(CC) $(CFLAGS) Song.cpp -o Song.o

SongPlaylist.o: SongPlaylist.cpp Song.h SongPlaylist.h
	$(CC) $(CFLAGS) SongPlaylist.cpp -o SongPlaylist.o

demo: demo.o $(COMPARE) $(SORT) Song.o SongPlaylist.o
	$(CC) $(COMPARE) $(SORT) Song.o SongPlaylist.o demo.o -o $(DEMO)

test: test.o $(COMPARE) $(SORT) Song.o SongPlaylist.o
	$(CC) $(COMPARE) $(SORT) Song.o SongPlaylist.o test.o -o $(TEST)

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
