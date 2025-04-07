#include <vector>
#include <list>
#include <cassert>
#include "realizacija.h"

namespace myHash {

class HashTable::Impl {
private:
   std::vector <std::list <std::pair <std::string, int> > > table;
   int capacity;
   int size = 0;
   
public: 
   Impl(const int& amountOfBuckets) {
      setCapacity(amountOfBuckets);
      table.resize(capacity);
   }
   Impl(const Impl& other) {
      this->table = other.table;
      this->capacity = other.capacity;
      this->size = other.size;
   }
   ~Impl() = default;
   
   int getSize() const {
      return size;
   }

   int getCapacity() const {
      return capacity;
   }

private:
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
      return sumOfChars % this->capacity;
   }

public:
   void insert(const std::string& key, const int& value) {
      if(size + 1 >= capacity) {
         rehash(capacity * 2);
      }
      try {
         find(key);
      } catch (const KeyNotFoundException& e) {
         int index = hashFunction(key);
         table[index].push_back(std::make_pair(key, value));
         ++size;
      }
   }

   int find(const std::string& key) const {
      int index = hashFunction(key);
      auto it = std::find_if(table[index].begin(), table[index].end(), 
         [&](const std::pair<std::string, int>& par) { return par.first == key; });
      if(it != table[index].end()) {
         return it->second;
      }
      else throw KeyNotFoundException();
   }

   void remove(const std::string& key) {
      int index = hashFunction(key);
      auto it = std::find_if(table[index].begin(), table[index].end(), 
         [&](const std::pair<std::string, int>& par) { return par.first == key; });
      if(it != table[index].end()) {
         table[index].erase(it);
         --size;
      }
      else throw KeyNotFoundException();
   }

   void rehash(const int& newCapacity) {
      if(newCapacity <= 0) throw std::invalid_argument("Error: Capacity must be greater than 0");
      setCapacity(newCapacity);
      std::vector <std::list <std::pair <std::string, int> > > oldTable(table);

      !(*this);
      table.resize(newCapacity);

      for(auto &eachBucket : oldTable) {
         for(const auto& pair : eachBucket) {
            insert(pair.first, pair.second);
         }
      }
   }

   Impl& operator= (const Impl& other) { // deep copy
      if (*this != other) {
         this->table = other.table;
         this->capacity = other.capacity;
         this->size = other.size;
      }
      return *this;
   }

   void operator! () {
      for(auto &eachBucket : table) {
         eachBucket.clear();
      }
      size = 0;
   }

   int operator[] (const std::string& key) {
      return find(key);
   }

   void operator() (const std::string& key, const int& value) {
      insert(key, value);
   }

   bool operator== (const Impl& other) const {
      return this->capacity == other.capacity &&
             this->size == other.size &&
             this->table == other.table;
   }

   bool operator!= (const Impl& other) const {
      return !(*this == other);
   }

   bool operator> (const Impl& other) const {
      return this->size > other.size;
   }

   std::string toString() const {
      std::string tableInfo = "\0";
      int index = 0;
      for(std::list<std::pair<std::string, int>> eachBucket : table) {
         if(capacity > 10) {
            if(!(eachBucket.empty())) {
               tableInfo += std::to_string(index) + ".";
               for(std::list<std::pair<std::string, int>>::iterator it = eachBucket.begin(); it != eachBucket.end(); ++it) {
                  tableInfo += "  " + it->first + " " + std::to_string(it->second);
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
};

HashTable::HashTable(const int& amountOfBuckets) : pImpl(std::make_unique<Impl>(amountOfBuckets)) { }
HashTable::HashTable(const HashTable& other) : pImpl(std::make_unique<Impl>(*other.pImpl)) { }
HashTable::~HashTable() = default;
HashTable& HashTable::operator= (const HashTable& other) { if (this != &other) pImpl = std::make_unique<Impl>(*other.pImpl); return *this;  }

int HashTable::getSize() const { return pImpl->getSize(); }
int HashTable::getCapacity() const { return pImpl->getCapacity(); }
void HashTable::insert(const std::string& key, const int& value) { pImpl->insert(key, value); }
void HashTable::remove(const std::string& key) { pImpl->remove(key); }
int HashTable::find(const std::string& key) const { return pImpl->find(key); }
void HashTable::rehash(const int& newCapacity) { pImpl->rehash(newCapacity); }

void HashTable::operator! () { pImpl->operator!(); }
int HashTable::operator[] (const std::string& key) const { return pImpl->operator[] (key); }
void HashTable::operator() (const std::string& key, const int& value) { pImpl->operator() (key, value);}
bool HashTable::operator== (const HashTable& other) const { return *pImpl == *other.pImpl; }
bool HashTable::operator!= (const HashTable& other) const { return *pImpl != *other.pImpl; }
bool HashTable::operator> (const HashTable& other) const { return *pImpl > *other.pImpl; }

std::string HashTable::toString() const { return pImpl->toString(); }
}