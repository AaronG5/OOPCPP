#include "SongPlaylist.h"

SongPlaylist::SongPlaylist(const SongPlaylist& other) {
   this->playlist = other.playlist;
   this->sorter = other.sorter ? other.sorter->clone() : nullptr;
}

void SongPlaylist::addSong(const std::string& title, const std::string& artist, const int& s) {
   playlist.push_back(std::make_shared<Song>(title, artist, s));
   if(sorter != nullptr) {
      sortPlaylist();
   }
}

void SongPlaylist::addSong(const std::string& title, const std::string& artist, const int& min, const int& s) {
   addSong(title, artist, min * 60 + s);
}

void SongPlaylist::addSong(std::shared_ptr<Song> song) {
   if(song == nullptr) {
      throw std::invalid_argument("Song points to null");
   }
   playlist.push_back(song);
   if(sorter != nullptr) {
      sortPlaylist();
   }
}

void SongPlaylist::removeSong(const std::string& title) {
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      if((*it)->getTitle() == title) {
         playlist.erase(it);
         return;
      }
   }
   throw std::invalid_argument("Song not found: " + title);
}

void SongPlaylist::addSongToOtherPlaylist(const std::string& title, SongPlaylist& other) {
   other.addSong(this->getSong(title));
}

void SongPlaylist::setSortMethod(const int& which) {
   switch(which) {
      case SORT_BY_LENGTH:
      sorter = std::make_unique<SortByLength>();
      break;
      case SORT_BY_TITLE:
      sorter = std::make_unique<SortByTitle>();
      break;
      case SORT_BY_ARTIST:
      // 3rd sorting method should go here
      break;
      default:
      throw std::out_of_range("Value out of range");
   }
}

void SongPlaylist::sortPlaylist() {
   if(sorter) { sorter->sortPlaylist(playlist); }
}

std::shared_ptr<Song> SongPlaylist::operator[] (const int& index) const {
   if(index < playlist.size()) { return playlist[index]; }
   else { throw std::out_of_range("Index value out of range"); }
}

SongPlaylist& SongPlaylist::operator= (const SongPlaylist& other) { 
   if(this == &other) { return *this; }
   this->playlist = other.playlist;
   this->sorter = other.sorter ? other.sorter->clone() : nullptr;
   return *this;
}

std::shared_ptr<Song> SongPlaylist::getSong(const std::string& title) const {
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      if((*it)->getTitle() == title) { return *it; }
   }
   throw std::invalid_argument("Song not found: " + title);
}

std::vector<std::shared_ptr<Song>> SongPlaylist::getPlaylist() const { return playlist; }

std::string SongPlaylist::getPlaylistInfo() const {
   std::stringstream ss;
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      ss << (*it)->getSongInfo() << std::endl;
   }
   return ss.str();
}