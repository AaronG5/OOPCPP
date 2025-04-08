#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "realizacija.h"

#define CAPACITY 10

using namespace myHash;
using namespace std;

bool isPassed = true;

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

   // Using operator `+=` override (insert)
   (*hash) += pair("Ron", 55); // ASCII value = 303
   (*hash) += pair("Anna", 66); // 382
   (*hash) += pair("Glorp", 77); // 516
   (*hash) += pair("Fin", 88); // 285
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
   try {
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
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Find unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Find unit tests PASSED.\n";
}

void copyTest() {
   try {
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
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Copy unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Copy unit tests PASSED.\n";
}

void sizeTest() {
   try {
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
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Size unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Size unit tests PASSED.\n";
}

void rehashTest() {
   try {
      cout << "\nRehash unit test output:\n";
      HashTable *test = new HashTable(CAPACITY);
      insertBestCase(test);
      insertWorstCase(test);
      cout << test->toString() << "\n";
      test->rehash(17);
      cout << test->toString();
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Rehash unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Rehash unit tests PASSED.\n";
}

void compareTest() {
   try {
      HashTable *test = new HashTable(CAPACITY);
   
      insertBestCase(test);
      HashTable testCopy1(*test);
      assert(test->equals(testCopy1));
      testCopy1.insert("Sin", 22);
      assert(*test != testCopy1);
   
      insertWorstCase(test);
      HashTable testCopy2(*test);
      test->insert("Rio", 33);
      test->insert("Eve", 111);
      assert(*test == testCopy2);
   
      assert(testCopy1 != testCopy2);
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Compare unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Compare unit tests PASSED.\n";
}

void removeTest() {
   try {
      HashTable *test1 = new HashTable(CAPACITY);
   
      insertBestCase(test1);
      HashTable testCopy(*test1);
      assert(*test1 == testCopy);
   
      test1->remove("Tom");
      assert(!(*test1 == testCopy));
   
      test1->insert("Tom", 44);
      assert(*test1 == testCopy);
   
      // Using operator `-=` override (remove)
      (*test1) -= "Anna";
      (*test1) -= "Jin";
      assert(!(*test1 == testCopy));
   
      HashTable *test2 = new HashTable(CAPACITY);
      insertWorstCase(test2);
      testCopy = *test2;
      assert(*test2 == testCopy);
   
      testCopy.remove("Rio");
      testCopy.remove("Eve");
      assert(!(*test2 == testCopy));
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Remove unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Remove unit tests PASSED.\n";
}

void clearTest() {
   try {
      HashTable *test = new HashTable(CAPACITY);
   
      insertBestCase(test);
      HashTable testCopy(*test);
      assert(*test == testCopy);
      !(*test);
      assert(!(*test == testCopy));
   } catch (const exception& e) {
      cout << e.what() << "\n";
      cout << "Clear unit tests FAILED.\n";
      isPassed = false;
      return;
   }
   cout << "Clear unit tests PASSED.\n";
}

void exceptionTest() {
   cout << "Testing custom exception...\n";

   HashTable *test = new HashTable(CAPACITY);
   insertBestCase(test);

   try {
      test->find("Thupten");
      assert(false); // Should never reach this
   } catch (const exception& e) {
      std::cout << "Caught: " << e.what() << "\n";
      try {
         test->remove("Bart");
         assert(false);
      } catch (const exception& e) {
         std::cout << "Caught: " << e.what() << "\n";
         cout << "Exception unit tests PASSED.\n";
         return;
      }
   }
   cout << "Exception unit tests FAILED.\n";
   isPassed = false;
}

void invalidCapacityTest() {
   try {
      HashTable *test = new HashTable(0);
      assert(false);
   } catch (const exception& e) {
      cout << "Caught: " << e.what() << "\n";
      try {
         HashTable *test = new HashTable(CAPACITY);
         test->rehash(-10);
         assert(false);
      } catch (const exception& e) {
         cout << "Caught: " << e.what() << "\n";
         cout << "invalidCapacity unit tests PASSED\n";
         return;
      }
   }
   cout << "invalidCapacity unit tests FAILED\n";
   isPassed = false;
}

int main() {

   cout << "Running class HashTable unit tests...\n\n";
   
   try {
      findTest();
      copyTest();
      sizeTest();
      rehashTest();
      compareTest();
      removeTest();
      clearTest();
      exceptionTest();
      invalidCapacityTest();
   } catch (...) {
      cout << "Unknown error occurred\n";
      isPassed = false;
   }

   cout << "\nUnit tests " << (isPassed ? "PASSED\n" : "FAILED\n");
   return 0;
}