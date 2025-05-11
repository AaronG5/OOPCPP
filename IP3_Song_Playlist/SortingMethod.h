#ifndef SORTING_METHOD_H
#define SORTING_METHOD_H

#include "SongPlaylist.h"
#include <vector>

class SortingMethod {
   public:
   virtual void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
   virtual ~SortingMethod() = default;
};

class SortByLength : public SortingMethod { // Using Tree Sort
   private:
   class Algorithm;
   std::unique_ptr<Algorithm> pImpl;

   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
};

class SortByTitle : public SortingMethod { // Using Gnome Sort (a.k.a. Stupid Sort)
   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
};

#endif