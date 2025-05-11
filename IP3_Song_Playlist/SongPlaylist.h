#ifndef SONG_PLAYLIST_H
#define SONG_PLAYLIST_H

#include "SortingMethod.h"
#include <vector>
#include <sstream>

#define SORT_BY_LENGTH 0
#define SORT_BY_TITLE 1
#define SORT_BY_ARTIST 2

class Song {
   private:
   static int nextId;
   int uniqueId;
   std::string title;
   std::string artist;
   int length; // Seconds

   public:
   Song(const std::string& title, const std::string& artist, const int& length);

   int getUniqueId() const;
   std::string getTitle() const;
   std::string getArtist() const;
   int getLength() const;
   std::string getSongInfo() const;
};


class SongPlaylist {
   private: 
   std::vector<std::shared_ptr<Song>> playlist;
   std::unique_ptr<SortingMethod> sorter;

   public:
   SongPlaylist();

   void addSong(const std::string& title, const std::string& artist, const int& length); // Create song and add to playlist, automatically sort by sorting method

   void addSong(std::shared_ptr<Song> song); // Pass song and add to playlist, automatically sort by sorting method

   void removeSong(const std::string& title); // Remove song from playlist by title

   void addSongToOtherPlaylist(const std::string& title, SongPlaylist& other); // Add song from current playlist to other playlist by searching for song title

   void sortPlaylist(); // sort playlist depending on sorting method

   void setSortMethod(const int& which);

   std::shared_ptr<Song> operator[] (const std::string& title) const; // Same as getSong

   std::shared_ptr<Song> getSong(const std::string& title) const;
   std::vector<std::shared_ptr<Song>> getPlaylist() const;
   std::string getPlaylistInfo() const; // return information for every Song from playlist in order
};

#endif