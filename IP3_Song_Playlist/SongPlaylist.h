// Aaron Gandžumian PS 2gr. 12-05-2025
// ID: 2413934
// aaron.gandzumian@mif.stud.vu.lt

// Structure of project:
// # SongPlaylist - represents a playlist used for storing 'Song' objects inside of its vector.
// # Song - represents a song that can be stored in 'SongPlaylist' instances.
// # CompareStrategy - fully virtual class used as a base class for deriving different ways of comparing songs to one another.
// # CompareByLength - method of comparing songs by their length. Derived from 'CompareStrategy'.
// # CompareByTitle - method of comparing songs by their title. Derived from 'CompareStrategy'.
// # CompareByArtist - method of comparing songs by their artist. Derived from 'CompareStrategy'. To be implemented by colleagues.
// # SortingAlgorithm - fully virtual class used as a base class for different sorting algorithms to sort the playlist.
// # TreeSort - a sorting algorithm based on binary search tree (BST). Derived from 'SortingAlgorithm`.
// # GnomeSort - a secondary sorting algorithm. Derived from 'SortingAlgorithm`.

// Methods included in 'SongPlaylist':
// # Deep copy constructor
// # 'addSong' - adds a song to the playlist, automatically sorting it by the currently set sorting method.
// # 'removeSong' - removes a song from the playlist.
// # 'addSongToOtherPlaylist' - copies a song from one playlist to another.
// # 'setSortMethod' - set sort method which will be used to sort the playlist when calling 'sortPlaylist'.
// # 'sortPlaylist' - sort the playlist by the method set using 'setSortMethod'. If no sorting method is set, the method won't do anything.
// # 'operator[]' - returns a pointer to a song from the playlist by its index.
// # 'operator=' - assigment operator override.
// # 'getSong' - returns a pointer to a song from the playlist by its title.
// # 'getPlaylist' - returns the vector which stores all the songs.
// # 'getPlaylistInfo' - returns a formatted string of the contents of the playlist vector.

// NOTE: EVERY SONG TITLE IS ASSUMED TO BE UNIQUE
// It would be easy to resolve this issue by accessing Song objects by their unique ID instead, but 
// for easier and more readable testing, Song objects are accessed by their titles.

#pragma once

#include "Song.h"
#include "SortingAlgorithm.h"
#include "CompareStrategy.h"
#include <vector>
#include <stdexcept>

#define SORT_BY_LENGTH 0
#define SORT_BY_TITLE 1
#define SORT_BY_ARTIST 2

class SongPlaylist {
   private: 
   std::vector<std::shared_ptr<Song>> playlist;
   std::unique_ptr<SortingAlgorithm> sorter;
   std::unique_ptr<CompareStrategy> comparator;

   public:
   SongPlaylist() = default;
   SongPlaylist(const SongPlaylist& other);

   void addSong(std::shared_ptr<Song> song); // Pass song and add to playlist and sort

   void removeSong(const std::string& title);

   void addSongToOtherPlaylist(const std::string& title, SongPlaylist& other);

   void setSortMethod(std::unique_ptr<SortingAlgorithm> sortAlgorithm, std::unique_ptr<CompareStrategy> compareStrat);

   void sortPlaylist();

   std::shared_ptr<Song> operator[] (const int& index) const; 
   SongPlaylist& operator= (const SongPlaylist& other);

   std::shared_ptr<Song> getSong(const std::string& title) const;
   std::vector<std::shared_ptr<Song>> getPlaylist() const;
   std::string getPlaylistInfo() const; 
};