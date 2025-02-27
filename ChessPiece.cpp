#include <iostream>

using namespace std;

class ChessPiece {
   private:
   static inline int amountOfObjects = 0;
   static inline int ID = 0;
   int id;
   const string type;
   const bool isWhite;
   bool isAlive;
   char xPos;
   int yPos;

   public:
   ChessPiece(string type, bool isWhite, bool isAlive, char xPos, int yPos) : 
   id(ID++), 
   type(type), 
   isWhite(isWhite), 
   isAlive(isAlive), 
   xPos(xPos), 
   yPos(yPos) {
      ++amountOfObjects;
   }
   
   static int getAmountOfObjects() {
      return amountOfObjects;
   }
   
   int getId() {
      return id;
   }

   private:
   // const string setType(const string type) {
   //    this->type = type;
   // }

   public:
   string getType(string type) const {
      return type;
   }

   bool getIsWhite() const {
      return isWhite;
   }

   bool getIsAlive() {
      return isAlive;
   }
   void setIsAlive(bool isAlive) {
      this->isAlive = isAlive;
   }

   char getXPos() {
      return xPos;
   }
   void setXPos(char xPos) {
      this->xPos = xPos;
   } 

   int getYPos() {
      return yPos;
   }
   void setYPos(int yPos) {
      this->yPos = yPos;
   }
   
   string toString() {
      return "ID: " + to_string(id) + "; type: " + type + "; isWhite: " + to_string(isWhite) + "; isAlive: " + to_string(isAlive) + "; xPosition: " + xPos + "; yPosition: " + to_string(yPos) + "\n";
   }


};

int main() {

   ChessPiece rook = ChessPiece("rook", true, true, 'a', 1);

   return 0;
}