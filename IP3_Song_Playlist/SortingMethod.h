#ifndef SORTING_METHOD_H
#define SORTING_METHOD_H

#include "SongPlaylist.h"
#include <vector>

class SortingMethod {
   public:
   virtual void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
};

#endif