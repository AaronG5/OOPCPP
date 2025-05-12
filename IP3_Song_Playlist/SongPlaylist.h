// Aaron Gandžumian PS 2gr. 12-05-2025
// ID: 2413934
// aaron.gandzumian@mif.stud.vu.lt

// Structure of project:
// # SongPlaylist - represents a playlist used for storing 'Song' objects inside of its vector.
// # Song - represents a song that can be stored in 'SongPlaylist' instances.
// # SortingMethod - fully virtual class used as a base class for different methods of sorting the playlist.
// # SortByLength - method of sorting the playlist by song length using Tree Sort. Derived from 'SortingMethod'.
// # SortByTitle - method of sorting the playlist by song title using Gnome Sort. Derived from 'SortingMethod'.
// # SortByArtist - method of sorting the playlist by song artist. Derived from 'SortingMethod'. To be implemented by colleagues.

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

#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H

#include "Song.h"
#include "SortingMethod.h"
#include <vector>
#include <stdexcept>

#define SORT_BY_LENGTH 0
#define SORT_BY_TITLE 1
#define SORT_BY_ARTIST 2

class SongPlaylist {
   private: 
   std::vector<std::shared_ptr<Song>> playlist;
   std::unique_ptr<SortingMethod> sorter;

   public:
   SongPlaylist() = default;
   SongPlaylist(const SongPlaylist& other);

   void addSong(const std::string& title, const std::string& artist, const int& s); // Create song, add to playlist and sort
   void addSong(const std::string& title, const std::string& artist, const int& min, const int& s); // Pass minutes and seconds as separate arguments

   void addSong(std::shared_ptr<Song> song); // Pass song and add to playlist and sort

   void removeSong(const std::string& title);

   void addSongToOtherPlaylist(const std::string& title, SongPlaylist& other);

   void setSortMethod(const int& which);

   void sortPlaylist();

   std::shared_ptr<Song> operator[] (const int& index) const; 
   SongPlaylist& operator= (const SongPlaylist& other);

   std::shared_ptr<Song> getSong(const std::string& title) const;
   std::vector<std::shared_ptr<Song>> getPlaylist() const;
   std::string getPlaylistInfo() const; 
};

#endif