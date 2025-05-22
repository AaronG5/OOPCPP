#pragma once

#include <string>
#include <sstream>

class Song {
   private:
   static int nextId;
   int uniqueId;
   std::string title;
   std::string artist;
   int length; // Seconds

   public:
   Song(const std::string& title, const std::string& artist, const int& length);
   Song(const std::string& title, const std::string& artist, const int& min, const int& s);

   int getUniqueId() const;
   std::string getTitle() const;
   std::string getArtist() const;
   int getLength() const;
   std::string getSongInfo() const;

   bool operator== (const std::shared_ptr<Song>& other) const;
};