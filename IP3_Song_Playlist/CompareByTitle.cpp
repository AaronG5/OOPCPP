#include "CompareStrategy.h"

bool CompareByTitle::compare(std::shared_ptr<Song> song1, std::shared_ptr<Song> song2) const {
   return song1->getTitle() < song2->getTitle();
}

std::unique_ptr<CompareStrategy> CompareByTitle::clone() const {
   return std::make_unique<CompareStrategy>();
}