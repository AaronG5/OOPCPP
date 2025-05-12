#include "SongPlaylist.h"

int Song::nextId = 0;

Song::Song(const std::string& title, const std::string& artist, const int& length) : 
   title(title), 
   artist(artist), 
   length(length) 
{
   uniqueId = nextId++;
}

int Song::getUniqueId() const { return uniqueId; }
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
int Song::getLength() const { return length; }
std::string Song::getSongInfo() const { 
   std::stringstream ss;
   ss << "Title: " << title << ". Artist: " << artist << ". Track length: " << length / 60 << "min. " << length % 60 << "s.";
   return ss.str();
}

bool Song::operator== (const std::shared_ptr<Song>& other) const {
   if(
      this->uniqueId == other->uniqueId ||
      (this->title == other->title &&
      this->artist == other->artist &&
      this->length == other->length)
      ) 
   {  return true; }
   else { return false; }
}