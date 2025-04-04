#include <vector>
#include <cassert>
#include "header.h"

namespace myHash {

class HashTable::Impl {
private:
   std::vector <std::vector <std::pair <std::string, int> > > table;
   int bucket;
   int size = 0;
   
public: 
   // Impl() {}
   Impl(const int& amountOfBuckets): bucket(amountOfBuckets) {
      table.resize(amountOfBuckets);
   }
   ~Impl() {}

   int hashFunction(const std::string& key) {
      int sumOfChars = 0;
      for(char c : key) {
         sumOfChars += c;
      }
      return sumOfChars % this->bucket;
   }

   void insert(const std::string& key, const int& value) {
      int index = hashFunction(key);
      table[index].push_back(std::make_pair(key, value));
      ++size;
   }

   void remove(const std::string& key) {
      int index = hashFunction(key);
      auto it = std::find_if(table[index].begin(), table[index].end(), 
         [&](const std::pair<std::string, int>& par) { return par.first == key; }); // Lambda function hell yeah!!!
      if(it != table[index].end()) {
         table[index].erase(it);
         --size;
      }
      else {} // throw exception "Key not found"
   }

   int find(const std::string& key) {
      int index = hashFunction(key);
      auto it = std::find_if(table[index].begin(), table[index].end(), 
         [&](const std::pair<std::string, int>& par) { return par.first == key; });
      if(it != table[index].end()) {
         return it->second;
      }
      else {
         // Throw exception maybe?
         return -1;
      }
   }

   int numOfObjects() {
      return size;
   }

};

HashTable::HashTable(const int& amountOfBuckets) : pImpl(std::make_unique<Impl>(amountOfBuckets)) { }
HashTable::~HashTable() = default;

int HashTable::hashFunction(const std::string& key) { return pImpl->hashFunction(key); }
void HashTable::insert(const std::string& key, const int& value) { pImpl->insert(key, value); }
void HashTable::remove(const std::string& key) { pImpl->remove(key); }
int HashTable::find(const std::string& key) { return pImpl->find(key); }
int HashTable::numOfObjects() { return pImpl->numOfObjects(); }

}