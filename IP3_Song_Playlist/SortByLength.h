#ifndef SORT_BY_LENGTH_H
#define SORT_BY_LENGTH_H

#include "SortingMethod.h"

class SortByLength : public SortingMethod {
   private:
   class Algorithm;
   std::unique_ptr<Algorithm> pImpl;

   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
};

#endif