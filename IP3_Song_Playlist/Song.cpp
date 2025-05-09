#include "Song.h"

int Song::nextId = 0;

Song::Song(const std::string& title, const std::string& artist, const int& length) : 
   title(title), 
   artist(artist), 
   length(length) 
{
   uniqueId = nextId++;
}

Song::~Song() = default;

int Song::getUniqueId() const { return uniqueId; }
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
int Song::getLength() const { return length; }
