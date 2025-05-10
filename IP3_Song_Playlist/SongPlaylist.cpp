#include "SongPlaylist.h"

SongPlaylist::SongPlaylist() { 
   playlist.resize(0); 
   sorter = nullptr;
}

SongPlaylist::~SongPlaylist() = default;

void SongPlaylist::addSong(const std::string& title, const std::string& artist, const int& length) {
   playlist.push_back(std::make_shared<Song>(title, artist, length));
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

std::vector<std::shared_ptr<Song>> SongPlaylist::getPlaylist() const { return playlist; }

std::string SongPlaylist::getPlaylistInfo() const {
   std::stringstream ss;
   for(auto it = playlist.begin(); it < playlist.end(); ++it) {
      ss << (*it)->getSongInfo() << std::endl;
   }
   return ss.str();
}