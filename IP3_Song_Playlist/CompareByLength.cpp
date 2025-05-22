#include "CompareStrategy.h"

bool CompareByLength::compare(std::shared_ptr<Song> song1, std::shared_ptr<Song> song2) const {
   return song1->getLength() < song2->getLength();
}

std::unique_ptr<CompareStrategy> CompareByLength::clone() const {
   return std::make_unique<CompareStrategy>();
}