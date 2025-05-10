#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H

#include "Song.h"
#include "SortingMethod.h"
#include <vector>

class SongPlaylist {
   private: 
   std::vector<std::shared_ptr<Song>> playlist;
   std::shared_ptr<SortingMethod> sorter;

   public:
   SongPlaylist();
   ~SongPlaylist();

   void addSong(const std::string& title, const std::string& artist, const int& length); // Add song to playlist and automatically sort by sorting method

   void removeSong(const std::string& title); // Remove song from playlist by title

   void addSongToOtherPlaylist(const std::string& title, SongPlaylist other); // Add song from current playlist to other playlist by searching for song title

   void sortPlaylist(); // sort playlist depending on sorting method

   void setSortMethod();

   std::vector<std::shared_ptr<Song>> getPlaylist() const;
   std::string getPlaylistInfo() const; // return information for every song from playlist in order

};

#endif