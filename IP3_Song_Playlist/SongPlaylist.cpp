#include "SongPlaylist.h"

SongPlaylist::SongPlaylist() { 
   playlist.resize(0); 
   sorter = nullptr;
}

void SongPlaylist::addSong(const std::string& title, const std::string& artist, const int& length) {
   playlist.push_back(std::make_shared<Song>(title, artist, length));
   if(sorter != nullptr) {
      sortPlaylist();
   }
}

void SongPlaylist::addSong(std::shared_ptr<Song> song) {
   playlist.push_back(song);
   if(sorter != nullptr) {
      sortPlaylist();
   }
}

void SongPlaylist::removeSong(const std::string& title) {
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      if((*it)->getTitle() == title) {
         playlist.erase(it);
         break;
      }
   }
}

void SongPlaylist::addSongToOtherPlaylist(const std::string& title, SongPlaylist& other) {
   other.addSong(this->getSong(title));
}

void SongPlaylist::sortPlaylist() {
   if(sorter) { sorter->sortPlaylist(playlist); }
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
   }
}

std::shared_ptr<Song> SongPlaylist::getSong(const std::string& title) const {
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      if((*it)->getTitle() == title) { return *it; }
   }
}

std::vector<std::shared_ptr<Song>> SongPlaylist::getPlaylist() const { return playlist; }

std::string SongPlaylist::getPlaylistInfo() const {
   std::stringstream ss;
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      ss << (*it)->getSongInfo() << std::endl;
   }
   return ss.str();
}