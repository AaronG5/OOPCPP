#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H

#include "Song.h"
#include "SortingMethod.h"
#include "SortByLength.h"
#include "SortByTitle.h"
#include <vector>

#define SORT_BY_LENGTH 0
#define SORT_BY_TITLE 1
#define SORT_BY_ARTIST 2

class SongPlaylist {
   private: 
   std::vector<std::shared_ptr<Song>> playlist;
   std::unique_ptr<SortingMethod> sorter;

   public:
   SongPlaylist();

   void addSong(const std::string& title, const std::string& artist, const int& length); // Add song to playlist and automatically sort by sorting method

   void addSong(std::shared_ptr<Song> song);

   void removeSong(const std::string& title); // Remove song from playlist by title

   void addSongToOtherPlaylist(const std::string& title, SongPlaylist& other); // Add song from current playlist to other playlist by searching for song title

   void sortPlaylist(); // sort playlist depending on sorting method

   void setSortMethod(const int& which);

   std::shared_ptr<Song> getSong(const std::string& title) const;
   std::vector<std::shared_ptr<Song>> getPlaylist() const;
   std::string getPlaylistInfo() const; // return information for every Song from playlist in order

};

#endif