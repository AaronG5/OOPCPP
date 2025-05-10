#ifndef SORT_BY_TITLE_H
#define SORT_BY_TITLE_H

#include "SortingMethod.h"

class SortByTitle : public SortingMethod {
   public:
   std::vector<std::shared_ptr<Song>> sortPlaylist(SongPlaylist playlist);
};

#endif
