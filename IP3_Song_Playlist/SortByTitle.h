#ifndef SORT_BY_TITLE_H
#define SORT_BY_TITLE_H

#include "SortingMethod.h"

class SortByTitle : public SortingMethod { // Using Gnome Sort (a.k.a. Stupid Sort)
   public:
   void sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist);
};

#endif