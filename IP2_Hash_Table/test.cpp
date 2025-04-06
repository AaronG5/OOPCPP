#include "header.h"
#include <cassert>
#include <iostream>

using namespace myHash;

int main() {
   int amount = 10;
   HashTable test1(amount);
   // HashTable *test1 = new HashTable(amount);
   
   try {
      
      // insert test
      test1.insert("Tim", 20); // ASCII value = 298
      test1.insert("Adam", 30); // ASCII value = 371
      test1.insert("Jin", 73); // ASCII value = 289
      test1.insert("Jiw", 60); // ASCII value = 298
   
      assert(test1.getSize() == 4);
   
      // copy test
      HashTable testCopy(test1);
      assert(testCopy.find("Tim") == 20);
      assert(testCopy.find("Adam") == 30);
      assert(testCopy.find("Jin") == 73);
      assert(testCopy.find("Jiw") == 60);
   
      // find test
      assert(test1.find("Tim") == 20);
      assert(test1.find("Adam") == 30);
      assert(test1.find("Jin") == 73);
      assert(test1.find("Jiw") == 60);
   
      // operator[] test (insertion)
      assert(test1["Tim"] == 20);
      assert(test1["Adam"] == 30);
      assert(test1["Jin"] == 73);
      assert(test1["Jiw"] == 60);
   
      std::cout << test1.toString();
   
      // operator== test (comparison)
      assert(test1 == testCopy);
   
      // delete test
      // test1.remove("Tim");
      // test1.remove("Adam");
      // test1.remove("Jin");
      // test1.remove("Jiw");
   
      // operator! test (clear table)
      !test1;
      
      assert(test1.getSize() == 0);

      // exception test
      testCopy.find("John");
      assert(false); // shouldn't be reached
   } 
   catch (const std::exception& e) {
      std::cout << e.what() << "\n";
   } 
   catch (...) {
      std::cout << "Unknown error occurred\n";
   }

   printf("Unit testing passed!\n");
   return 0;
}