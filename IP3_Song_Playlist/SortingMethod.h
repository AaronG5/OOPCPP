#ifndef SORTING_METHOD_H
#define SORTING_METHOD_H

#include "SongPlaylist.h"
#include <vector>

class SortingMethod {
   public:
   virtual std::vector<std::shared_ptr<Song>> sortPlaylist(SongPlaylist playlist) = 0;
};

#endif