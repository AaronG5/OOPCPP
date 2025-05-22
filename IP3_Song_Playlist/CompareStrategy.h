#pragma once

#include <memory>
#include "Song.h"

class CompareStrategy {
   public:
   virtual ~CompareStrategy() = default;
   virtual bool compare(std::shared_ptr<Song> song1, std::shared_ptr<Song> song2) const = 0;
   virtual std::unique_ptr<CompareStrategy> clone() const = 0;
};

class CompareByLength : public CompareStrategy {
   public:
   bool compare(std::shared_ptr<Song> song1, std::shared_ptr<Song> song2) const; // using `<`
   std::unique_ptr<CompareStrategy> clone() const;
};

class CompareByTitle : public CompareStrategy {
   public:
   bool compare(std::shared_ptr<Song> song1, std::shared_ptr<Song> song2) const; // using `<`
   std::unique_ptr<CompareStrategy> clone() const;
};