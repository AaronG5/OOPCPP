// Demonstration of HashTable class usage in a real world scenario

#include <vector>
#include <iostream>
#include "realizacija.h"

using namespace myHash;
using namespace std;

int main() {
   cout << "<<<< Hash Table Demonstration >>>>\n" << "Implementing hash table in a student database made for storing the students' names and IDs";
   try {
      HashTable *db = new HashTable(5);
   
      cout << "Inserting students: Mary(ID:50123), Leo(ID:60184), Jack(ID:27924), Bill(ID:79215)...\n";
      db->insert("Mary", 50123);
      db->insert("Leo", 60184);
      (*db)("Jack", 27924);
      (*db)("Bill", 79215);
   
      cout << "Capacity of possible student entries in database: " << db->getCapacity() << "\nAmount of students entered into database: " << db->getSize() << "\n";

      cout << "By adding 2 more students, the database automatically doubles in size to ensure fast insertion, deletion and search functionality.\n";
      cout << "Inserting students: Joe(ID:89261), Michael(ID:92156)\n";
      db->insert("Joe", 89261);
      db->insert("Michael", 92156);

      cout << "Mary gets expelled, meaning she needs to be removed from the database.\n";
      db->remove("Mary");

      cout << "The administration needs to make a copy of the database for unknown reasons.\n";
      HashTable *dbCopy = new HashTable(*db);

      cout << "The administration wants to check if the student's name matches with his ID.\nLooking up ID of Michael...\n";
      cout << "Michael's student ID is: " << to_string(db->find("Michael")) << "\n";

      cout << "The administration would like to clear the copied database and use it for other data storage\n";
      !(*dbCopy);

      cout << "The administration would like to check whether it was able to successfully clear the copied database.\n";
      cout << "The clearing of copied database was: " << (*dbCopy == *db && dbCopy->getSize() == 0) ? "unsuccessful.\n" : "successful.\n";

      cout << "Leo's student ID is 60184: " << ((*db)["Leo"] == 60184) ? "True\n" : "False\n"; 


   } catch (const exception& e) {
      cout << "Caught: " << e.what() << "\n";
   }

   cout << "<<<< Demo Complete >>>>";
   return 0;
}