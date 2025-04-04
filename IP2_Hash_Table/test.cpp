#include "header.h"
#include <cassert>

using namespace myHash;

int main() {
   int amount = 10;
   HashTable test1(amount);
   // HashTable *test1 = new HashTable(amount);
   
   // hashFunction test
   assert(test1.hashFunction("Aa") == 2);
   assert(test1.hashFunction("Tim") == 8);
   
   // insert test
   test1.insert("Tim", 20); // ASCII value = 298
   test1.insert("Adam", 30); // ASCII value = 371
   test1.insert("Jim", 73); // ASCII value = 288
   test1.insert("Jiw", 60); // ASCII value = 298

   assert(test1.numOfObjects() == 4);

   // find test
   assert(test1.find("Tim") == 20);
   assert(test1.find("Adam") == 30);
   assert(test1.find("Jim") == 73);
   assert(test1.find("Jiw") == 60);
   assert(test1.find("John") == -1);


   // delete test
   test1.remove("Tim");
   test1.remove("Adam");
   test1.remove("Jim");
   test1.remove("Jiw");
   
   assert(test1.numOfObjects() == 0);

   printf("Hi!\n");
   return 0;
}