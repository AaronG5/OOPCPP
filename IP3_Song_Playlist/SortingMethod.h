#ifndef SORTING_METHOD_H
#define SORTING_METHOD_H

#include "Song.h"
#include <vector>

class SortingMethod {
   public:
   virtual ~SortingMethod() = default;
   virtual void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist) = 0;
   virtual std::unique_ptr<SortingMethod> clone() const = 0;
};

class SortByLength : public SortingMethod { // Using Tree Sort
   private:
   class Impl;
   std::unique_ptr<Impl> pImpl;

   public:
   SortByLength();
   ~SortByLength();
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
   std::unique_ptr<SortingMethod> clone() const;
};

class SortByTitle : public SortingMethod { // Using Gnome Sort (a.k.a. Stupid Sort)
   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
   std::unique_ptr<SortingMethod> clone() const;
};

#endif