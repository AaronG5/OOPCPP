#ifndef SORT_BY_LENGTH_H
#define SORT_BY_LENGTH_H

#include "SortingMethod.h"

class SortByLength : public SortingMethod {
   public:
   std::vector<std::shared_ptr<Song>> sortPlaylist(SongPlaylist playlist);
};

#endif