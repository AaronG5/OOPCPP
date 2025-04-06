// Aaron Gandžumian
// 01-04-2025
// aaron.gandzumian@mif.stud.vu.lt

#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <cstddef>

namespace myHash {
   
   class KeyNotFoundException : public std::exception {
   public:
      const char *what() const noexcept override {
         return "Error: Couldn't find key";
      }
   };

   class HashTable {
      private:
      class Impl;
      std::unique_ptr<Impl> pImpl;
   
   public:
   HashTable(const int& amountOfBuckets);
   HashTable(const HashTable& other); // Copy constructor
   ~HashTable();
   
   int getSize() const; // Return number of objects in hash table
   int getCapacity() const;
   void setCapacity(const int& capacity);
   void insert(const std::string& key, const int& value); // Insert key-value pair by key
   void remove(const std::string& key); // Remove key-value pair by key
   int find(const std::string& key) const; // Find value by key
   
   void operator!(); // Clear whole table
   int operator[] (const std::string& key) const; // Search table by key, return value
   void operator() (const std::string& key, const int& value); // Insert key-value pair
   bool operator== (const HashTable& other) const; // Is the same table in terms of content
   bool operator> (const HashTable& other) const; // Is greater than other table based on number of elements
   
   std::string toString() const;
   
   // TODO: Add iterator functions
   };
}

#endif