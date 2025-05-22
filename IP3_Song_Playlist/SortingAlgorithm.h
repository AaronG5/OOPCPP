#pragma once

#include "Song.h"
#include "CompareStrategy.h"
#include <vector>

class SortingAlgorithm {
   public:
   virtual ~SortingAlgorithm() = default;
   virtual void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist, const std::unique_ptr<CompareStrategy>& comparator) = 0;
   virtual std::unique_ptr<SortingAlgorithm> clone() const = 0;
};

class TreeSort : public SortingAlgorithm { // Using Tree Sort
   private:
   class Impl;
   std::unique_ptr<Impl> pImpl;

   public:
   TreeSort();
   ~TreeSort();
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist, const std::unique_ptr<CompareStrategy>& comparator);
   std::unique_ptr<SortingAlgorithm> clone() const;
};

class GnomeSort : public SortingAlgorithm { // Using Gnome Sort (a.k.a. Stupid Sort)
   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist, const std::unique_ptr<CompareStrategy>& comparator);
   std::unique_ptr<SortingAlgorithm> clone() const;
};