// Aaron Gandžumian
// 01-04-2025
// aaron.gandzumian@mif.stud.vu.lt

#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <cstddef>

namespace myHash {
   class HashTable {
   private:
      class Impl;
      std::unique_ptr<Impl> pImpl;

   public:
      HashTable(const int& amountOfBuckets);
      ~HashTable();

      int hashFunction(const std::string& key);
      void insert(const std::string& key, const int& value);
      void remove(const std::string& key);
      int find(const std::string& key);
      int numOfObjects(); // Return number of objects in hash table

      // void operator! (); // clear whole hash table
      // int operator[] (std::string key); // placeholder, search table by key
      // void operator() (); // deep copy 
      // void operator== (HashTable table); // compare hash table keys/values

      // TODO: Add iterator functions
   };
}

#endif