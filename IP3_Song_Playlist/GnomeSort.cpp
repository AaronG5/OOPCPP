#include "SortingAlgorithm.h"

void GnomeSort::sortPlaylist(std::vector<std::shared_ptr<Song>>& playlist, const std::unique_ptr<CompareStrategy>& comparator) {
   int index = 0;
   int size = playlist.size();

   while(index != size) {
      if(index == 0) { ++index; }
      else if(comparator->compare(playlist[index], playlist[index-1])) { 
         std::swap(playlist[index], playlist[index-1]);
         --index;
      }
      else { ++index; }
   }
}

std::unique_ptr<SortingAlgorithm> GnomeSort::clone() const {
   return std::make_unique<GnomeSort>();
}