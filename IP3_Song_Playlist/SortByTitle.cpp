#include "SortingMethod.h"

void SortByTitle::sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist) {
   int index = 0;
   int size = playlist.size();

   while(index != size) {
      if(index == 0) { ++index; }

      if(playlist[index]->getTitle() >= playlist[index-1]->getTitle()) { ++index; }
      else {
         std::swap(playlist[index], playlist[index-1]);
         --index;
      }
   }
}

std::unique_ptr<SortingMethod> SortByTitle::clone() const {
   return std::make_unique<SortByTitle>();
}