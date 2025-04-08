#include <vector>
#include <list>
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include "realizacija.h"

namespace myHash {

class KeyNotFoundException : public std::exception {
public:
   const char* what() const noexcept override {
      return "Error: Couldn't find key";
   }
};

class HashTable::Impl {
private:
   std::vector <std::list <std::pair <std::string, int> > > table;
   int capacity;
   int size = 0;
   
   void setCapacity(const int& capacity) {
      if(capacity > 0) {
         this->capacity = capacity;
      }
      else throw std::invalid_argument("Error: Capacity must be greater than 0");
   }

   int hashFunction(const std::string& key) const {
      int sumOfChars = 0;
      for(char c : key) {
         sumOfChars += c;
      }
      return sumOfChars % capacity;
   }

   friend HashTable;
};

HashTable::HashTable(const int& amountOfBuckets) : pImpl(std::make_unique<Impl>()) {
   pImpl->setCapacity(amountOfBuckets);
   pImpl->table.resize(amountOfBuckets);
}

HashTable::HashTable(const HashTable& other) : pImpl(std::make_unique<Impl>()) { 
   pImpl->capacity = other.pImpl->capacity;
   pImpl->size = other.pImpl->size;

   pImpl->table.resize(other.pImpl->capacity);
   for (int i = 0; i < other.pImpl->capacity; ++i) {
      pImpl->table[i] = other.pImpl->table[i];
   }
}

HashTable::~HashTable() = default;

HashTable& HashTable::operator= (const HashTable& other) { 
   if (this != &other) pImpl = std::make_unique<Impl>(*other.pImpl); 
   return *this;  
}

int HashTable::getSize() const { 
   return pImpl->size; 
}

int HashTable::getCapacity() const { 
   return pImpl->capacity; 
}

void HashTable::insert(const std::string& key, const int& value) { 
   if(pImpl->size + 1 >= pImpl->capacity) {
      rehash(pImpl->capacity * 2);
   }
   try {
      find(key);
   } catch (const KeyNotFoundException& e) {
      int index = pImpl->hashFunction(key);
      pImpl->table[index].push_back(std::make_pair(key, value));
      ++(pImpl->size);
   }
}

int HashTable::find(const std::string& key) const { 
   int index = pImpl->hashFunction(key);
   auto it = std::find_if(pImpl->table[index].begin(), pImpl->table[index].end(), 
      [&](const std::pair<std::string, int>& par) { return par.first == key; });
   if(it != pImpl->table[index].end()) {
      return it->second;
   }
   else throw KeyNotFoundException();
}

void HashTable::remove(const std::string& key) { 
   int index = pImpl->hashFunction(key);
   auto it = std::find_if(pImpl->table[index].begin(), pImpl->table[index].end(), 
      [&](const std::pair<std::string, int>& par) { return par.first == key; });
   if(it != pImpl->table[index].end()) {
      pImpl->table[index].erase(it);
   }
   else throw KeyNotFoundException();
}

void HashTable::rehash(const int& newCapacity) { 
   if(newCapacity < pImpl->size) throw std::invalid_argument("Error: Capacity must be greater than current size.");
   pImpl->setCapacity(newCapacity);
   std::vector <std::list <std::pair <std::string, int> > > oldTable(pImpl->table);

   !(*this);
   pImpl->table.resize(newCapacity);

   for(auto &eachBucket : oldTable) {
      for(const auto& pair : eachBucket) {
         insert(pair.first, pair.second);
      }
   }
}

bool HashTable::equals(const HashTable& other) const {  // Don't know if correct
   return pImpl->capacity == other.pImpl->capacity &&
      pImpl->size == other.pImpl->size &&
      pImpl->table == other.pImpl->table;
}

void HashTable::operator! () { 
   for(auto &eachBucket : pImpl->table) {
      eachBucket.clear();
   }
   pImpl->size = 0;
}

int HashTable::operator[] (const std::string& key) const { 
   return find(key); 
}

void HashTable::operator+= (const std::pair<std::string, int>& p) { 
   insert(p.first, p.second); 
}

void HashTable::operator-= (const std::string& key) { 
   remove(key); 
}

bool HashTable::operator== (const HashTable& other) const { 
   return pImpl->size == other.pImpl->size; 
}

bool HashTable::operator!= (const HashTable& other) const { 
   return pImpl->size != other.pImpl->size; 
}

bool HashTable::operator> (const HashTable& other) const { 
   return  pImpl->size > other.pImpl->size; 
}

bool HashTable::operator>= (const HashTable& other) const {
   return pImpl->size >= other.pImpl->size; 
}

bool HashTable::operator< (const HashTable& other) const {
   return pImpl->size < other.pImpl->size; 
}

bool HashTable::operator<= (const HashTable& other) const {
   return pImpl->size <= other.pImpl->size; 
}

std::string HashTable::toString() const {
   std::string tableInfo = "\0";
   int index = 0;
   for(std::list<std::pair<std::string, int>> eachBucket : pImpl->table) {
      if(pImpl->capacity > 10) {
         if(!(eachBucket.empty())) {
            tableInfo += std::to_string(index) + ".";
            for(std::list<std::pair<std::string, int>>::iterator it = eachBucket.begin(); it != eachBucket.end(); ++it) {
               tableInfo += " " + it->first + " " + std::to_string(it->second);
            }
            tableInfo += "\n";
         }
      }
      else {
         tableInfo += std::to_string(index) + ".";
         for(std::list<std::pair<std::string, int>>::iterator it = eachBucket.begin(); it != eachBucket.end(); ++it) {
            tableInfo += "  " + it->first + " " + std::to_string(it->second);
         }
         tableInfo += "\n";
      }
      ++index;
   }
   return tableInfo;
}
}