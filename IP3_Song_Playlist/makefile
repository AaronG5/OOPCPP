CC = g++
CFLAGS = -std=c++17 -Wall -Wextra -c -Wno-self-assign-overloaded -Wno-unused-variable

SORT = SortByLength.o SortByTitle.o #SortByArtist.o
HEADER = Song.h SongPlaylist.h SortingMethod.h

TEST = Test
DEMO = Demo

TEST_LOG = log.txt

demo.o: demo.cpp $(HEADER)
	$(CC) $(CFLAGS) demo.cpp -o demo.o

test.o: test.cpp $(HEADER)
	$(CC) $(CFLAGS) test.cpp -o test.o

SortByLength.o: SortByLength.cpp $(HEADER)
	$(CC) $(CFLAGS) SortByLength.cpp -o SortByLength.o

SortByTitle.o: SortByTitle.cpp $(HEADER)
	$(CC) $(CFLAGS) SortByTitle.cpp -o SortByTitle.o

#SortByArtist.o: SortByArtist.cpp $(HEADER)
#	$(CC) $(CFLAGS) SortByArtist.cpp -o SortByArtist.o

Song.o: Song.cpp Song.h
	$(CC) $(CFLAGS) Song.cpp -o Song.o

SongPlaylist.o: SongPlaylist.cpp Song.h SongPlaylist.h
	$(CC) $(CFLAGS) SongPlaylist.cpp -o SongPlaylist.o

demo: demo.o $(SORT) Song.o SongPlaylist.o
	$(CC) $(SORT) Song.o SongPlaylist.o demo.o -o $(DEMO)

test: test.o $(SORT) Song.o SongPlaylist.o
	$(CC) $(SORT) Song.o SongPlaylist.o test.o -o $(TEST)

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
