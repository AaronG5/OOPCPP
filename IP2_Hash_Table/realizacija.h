/* 
Aaron Gandžumian PS 2gr. 01-04-2025
ID: 2413934
aaron.gandzumian@mif.stud.vu.lt

This header file defines the implementation of a hash table using separate chaining.

The hash table stores key-value pairs, assuming every key is unique, and uses a vector of linked lists (std::vector of std::list of std::pair) to handle collisions.
   Key = string; Value = int; Can be adapted for any kind of data.

Collision resolution: When two key-value pairs are trying to access the same index value, they are instead stored in the same list (separate chaining).
Hash table resizing and rehashing: hash table automatically increases capacity by a factor of 2 once size == capacity

Primary hash table functions (all lookups, deletions, etc. are done using key):
- Insert key-value pair                   [ insert(string, int) ]
- Remove key-value pair                   [ remove(string) ]
- Find value by key                       [ find(string) ]
- Resize table and rehash key-value pairs [ rehash(int) ]
- Check whether two tables are the same   [ equals(HashTable) ]

- Operator overloads:
   - `!` clear table of all key-value pairs and free allocated memory of data
   - `+=` insert key-value pair
   - `-=` remove key-value pair by key
   - `[]` find value by key
   - `==` compare whether two tables are equal based on number of elements
   - `>` compare whether one table is bigger than the other based on the number of elements
   - `>=` compare whether one table is bigger than or equal to the other based on the number of elements
   - `<` compare whether one table is less than the other based on the number of elements
   - `<=` compare whether one table is less than or equal to the other based on the number of elements

Class provides basic exception handling through `KeyNotFoundException` class. Exception is thrown whenever key is not found during lookup or removal.

The implementation uses the PImpl (Pointer to Implementation) idiom for better separation of interface and implementation and maintaining
principles of encapsulation.

Deep copying of created hash tables is possible using deep copy constructor or overriden `operator=`.

`toString` method outputs content of all buckets (empty or full) if the capacity of the table doesn't exceed 10, otherwise only the buckets with 
values stored inside are outputed.
*/

#ifndef HEADER_H
#define HEADER_H

#include <string>
#include <utility>
#include <memory>

namespace myHash {

   class HashTable {
   private:
      class Impl;
      std::unique_ptr<Impl> pImpl;
   
   public:
   HashTable(const int& amountOfBuckets);
   HashTable(const HashTable& other); // Deep copy constructor
   HashTable& operator= (const HashTable& other); // Copy
   ~HashTable();
   
   int getSize() const; // Return number of objects in hash table
   int getCapacity() const; // Return amount of buckets in hash table
   void insert(const std::string& key, const int& value); // Insert key-value pair by key
   int find(const std::string& key) const; // Find value by key
   void remove(const std::string& key); // Remove key-value pair by key
   void rehash(const int& newCapacity); // Resize and rehash all key-value pairs
   bool equals(const HashTable& other) const; // Is hash table the same as other hash table
   
   void operator!(); // Clear whole table
   int operator[] (const std::string& key) const; // Search table by key, return value
   void operator+= (const std::pair<std::string, int>& p); // Insert key-value pair
   void operator-= (const std::string& key); // Remove key-value pair
   bool operator== (const HashTable& other) const; // Is equal to other table based on number of elements
   bool operator!= (const HashTable& other) const; // Is not equal to other table based on number of elements
   bool operator> (const HashTable& other) const; // Is greater than other table based on number of elements
   bool operator>= (const HashTable& other) const; // Is greater than or equal to other table based on number of elements
   bool operator< (const HashTable& other) const; // Is less than other table based on number of elements
   bool operator<= (const HashTable& other) const; // Is less than or equal to other table based on number of elements
   
   std::string toString() const;
   };
}

#endif