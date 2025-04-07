#include "header.h"
#include <cassert>
#include <iostream>

#define CAPACITY 10

using namespace myHash;
using namespace std;

// TODO: Finish unit tests and make demo.cpp

void insertBestCase(HashTable *hash);
void insertWorstCase(HashTable *hash);

void findTest();
void copyTest();
void sizeTest();
void rehashTest();
void compareTest();
void removeTest();
void clearTest();
void exceptionTest();

void insertBestCase(HashTable *hash) {
   // Using `insert` method
   hash->insert("Tim", 11); // ASCII value = 298
   hash->insert("Adam", 22); // 371
   hash->insert("Jin", 33); // 289
   hash->insert("Tom", 44); // 304

   // Using operator `()` override (insert)
   (*hash)("Ron", 55); // ASCII value = 303
   (*hash)("Anna", 66); // 382
   (*hash)("Glorp", 77); // 516
   (*hash)("Fin", 88); // 285
}

void insertWorstCase(HashTable *hash) {
   hash->insert("Tim", 11); // ASCII value = 298
   hash->insert("Sin", 22); // 298
   hash->insert("Rio", 33); // 298
   hash->insert("Jim", 44); // 288
   hash->insert("Leo", 55); // 288
   hash->insert("Eve", 66); // 288
   hash->insert("Sal", 77); // 288
   hash->insert("Adil", 88); // 378
}

void findTest() {
   HashTable *test = new HashTable(CAPACITY);
   {
      insertBestCase(test);

      // Using `find` method
      assert(test->find("Tim") == 11);
      assert(test->find("Adam") == 22);
      assert(test->find("Jin") == 33);
      assert(test->find("Tom") == 44);

      // Using operator `[]` override (find)
      assert((*test)["Ron"] == 55);
      assert((*test)["Anna"] == 66);
      assert((*test)["Glorp"] == 77);
      assert((*test)["Fin"] == 88);
   }
   {
      insertWorstCase(test);

      // Using `find` method
      assert(test->find("Tim") == 11);
      assert(test->find("Sin") == 22);
      assert(test->find("Rio") == 33);
      assert(test->find("Jim") == 44);

      // Using operator `[]` override (find)
      assert((*test)["Leo"] == 55);
      assert((*test)["Eve"] == 66);
      assert((*test)["Sal"] == 77);
      assert((*test)["Adil"] == 88);
   }

   cout << "Find unit tests passed.\n";
}

void copyTest() {
   HashTable *test = new HashTable(CAPACITY);
   {
      insertBestCase(test);
      HashTable testCopy(*test);

      assert(testCopy.find("Tim") == 11);
      assert(testCopy.find("Adam") == 22);
      assert(testCopy.find("Jin") == 33);
      assert(testCopy.find("Tom") == 44);
      assert(testCopy.find("Ron") == 55);
      assert(testCopy.find("Anna") == 66);
      assert(testCopy.find("Glorp") == 77);
      assert(testCopy.find("Fin") == 88);
   }
   {
      insertWorstCase(test);
      HashTable testCopy(CAPACITY + 4);
      testCopy = *test;

      assert(testCopy.find("Tim") == 11);
      assert(testCopy.find("Sin") == 22);
      assert(testCopy.find("Rio") == 33);
      assert(testCopy.find("Jim") == 44);
      assert(testCopy.find("Leo") == 55);
      assert(testCopy.find("Eve") == 66);
      assert(testCopy.find("Sal") == 77);
      assert(testCopy.find("Adil") == 88);

      testCopy = testCopy;
   }

   cout << "Copy unit tests passed.\n";
}

void sizeTest() { // Check if size increases when we input the same key value pair
   HashTable *test = new HashTable(CAPACITY);

   assert(test->getSize() == 0);
   test->insert("Tim", 11);
   assert(test->getSize() == 1);
   test->insert("Adam", 22);
   assert(test->getSize() == 2);
   test->insert("Jin", 33);
   assert(test->getSize() == 3);
   test->insert("Tom", 44);
   assert(test->getSize() == 4);
   test->insert("Tom", 55);
   assert(test->getSize() == 4);

   cout << "Size unit tests passed.\n";
}

void rehashTest() {
   cout << "\nRehash unit test output:\n";
   HashTable *test = new HashTable(CAPACITY);
   insertBestCase(test);
   cout << test->toString() << "\n";
   insertWorstCase(test);
   cout << test->toString() << "\n";
   test->rehash(17);
   cout << test->toString() << "\n";
   test->rehash(3);
   cout << test->toString() << "\n";
   
   cout << "Rehash unit tests passed.\n";
}

void compareTest() {
   HashTable *test = new HashTable(CAPACITY);

   insertBestCase(test);
   HashTable testCopy1(*test);
   assert(*test == testCopy1);
   testCopy1.insert("Sin", 22);
   assert(*test != testCopy1);

   insertWorstCase(test);
   HashTable testCopy2(*test);
   test->insert("Rio", 33);
   test->insert("Eve", 111);
   assert(*test == testCopy2);

   assert(!(testCopy1 == testCopy2));

   cout << "Compare unit tests passed.\n";
}

void removeTest() {
   HashTable *test1 = new HashTable(CAPACITY);

   insertBestCase(test1);
   HashTable testCopy(*test1);
   assert(*test1 == testCopy);

   test1->remove("Tom");
   assert(!(*test1 == testCopy));

   test1->insert("Tom", 44);
   assert(*test1 == testCopy);

   test1->remove("Anna");
   test1->remove("Jin");
   assert(!(*test1 == testCopy));

   HashTable *test2 = new HashTable(CAPACITY);
   insertWorstCase(test2);
   testCopy = *test2;
   assert(*test2 == testCopy);

   testCopy.remove("Rio");
   testCopy.remove("Eve");
   assert(!(*test2 == testCopy));

   cout << "Remove unit tests passed.\n";
}

void clearTest() {
   cout << "\nClear unit test output:\n";

   HashTable *test = new HashTable(CAPACITY);

   insertBestCase(test);
   HashTable testCopy(*test);
   assert(*test == testCopy);
   cout << test->toString() << "\n";
   !(*test);
   assert(!(*test == testCopy));
   cout << test->toString() << "\n";

   cout << "Clear unit tests passed.\n";
}

void exceptionTest() {
   cout << "Testing custom exception...\n";

   HashTable *test = new HashTable(CAPACITY);
   insertBestCase(test);

   try {
      test->find("Thupten");
      assert(false); // Should never reach this
   } catch (const KeyNotFoundException& e) {
      std::cout << "Caught: " << e.what() << "\n";
   }

   try {
      test->remove("Bart");
      assert(false);
   } catch (const KeyNotFoundException& e) {
      std::cout << "Caught: " << e.what() << "\n";
   }
   cout << "Exception unit tests passed.\n";
}

void invalidCapacityTest() {
   try {
      HashTable *test = new HashTable(0);
      assert(false);
   } catch (const exception& e) {
      cout << "Caught: " << e.what() << "\n";
   }

   try {
      HashTable *test = new HashTable(CAPACITY);
      test->rehash(-10);
      assert(false);
   } catch (const exception& e) {
      cout << "Caught: " << e.what() << "\n";
   }
}

int main() {

   cout << "Running class HashTable unit tests...\n";
   
   try {
      findTest();
      copyTest();
      sizeTest();
      rehashTest();
      compareTest();
      removeTest();
      clearTest();
   } catch (const exception& e) {
      cout << e.what() << "\n";
   } catch (...) {
      cout << "Unknown error occurred\n";
   }

   exceptionTest();

   printf("Unit tests passed!\n");
   return 0;
}