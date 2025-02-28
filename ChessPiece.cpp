#include <iostream>
#include <exception>
#include <stdexcept>
#include <cctype>
#include <assert.h>

using namespace std;

class ChessPiece {
   private:
   int id;
   const string type;
   const bool isWhite;
   bool isAlive;
   char xPos;
   int yPos;
   
   public:
   static int amountOfObjects;
   static int ID;

   ChessPiece(string type, bool isWhite, bool isAlive, char xPos, int yPos) : 
   id(ID++), 
   type(validateType(type)), 
   isWhite(isWhite), 
   isAlive(isAlive) {
      ++amountOfObjects;
      setXPos(xPos);
      setYPos(yPos);
   }

   private:
   string validateType(string type) const{
      for(char &c : type) {
         c = tolower(c);
      }
      if(type == "king" || type == "queen" || type == "rook" 
         || type == "bishop" || type == "knight" || type == "pawn") {
         return type;
      }
      else {
         throw(runtime_error("Error. Not a valid chess piece type.\n"));
      }
   }

   void setIsAlive(bool isAlive) {
      this->isAlive = isAlive;
   }
   
   void setXPos(char xPos) {
      xPos = tolower(xPos);
      // (xPos >= 'a' && xPos <= 'h') 
      // ? this->xPos = xPos 
      // : throw(runtime_error("Invalid input.\n"));
      if(xPos >= 'a' && xPos <= 'h') {
         this->xPos = xPos;
      }
      else {
         throw(runtime_error("Error. Invalid X position value.\n"));
      }
   } 
   
   void setYPos(int yPos) {
      // (yPos > 0 && yPos < 9) ? this->yPos = yPos : throw(runtime_error("Invalid input.\n"));
      if(yPos > 0 && yPos < 9) {
         this->yPos = yPos;
      }
      else {
         throw(runtime_error("Error. Invalid Y position value.\n"));
      }
   }

   public:
   ~ChessPiece() {
      --amountOfObjects;
   }
   
   static int getAmountOfObjects() {
      return amountOfObjects;
   }
   
   int getId() {
      return id;
   }
   
   string getType() const {
      return type;
   }

   bool getIsWhite() const {
      return isWhite;
   }

   bool getIsAlive() {
      return isAlive;
   }

   char getXPos() {
      return xPos;
   }

   int getYPos() {
      return yPos;
   }
   
   string toString() {
      return "ID: " + to_string(id) + "; type: " + type + "; isWhite: " + to_string(isWhite) + "; isAlive: " 
      + to_string(isAlive) + "; xPosition: " + xPos + "; yPosition: " + to_string(yPos) + "\n";
   }

   void killPiece() {
      setIsAlive(false);
   }

   void movePiece(char xPos, int yPos) {
      setXPos(xPos);
      setYPos(yPos);
   }
};

int ChessPiece::amountOfObjects = 0;
int ChessPiece::ID = 0;

int main() {

   try {

      ChessPiece *chessPieceArray[5];

      chessPieceArray[0] = new ChessPiece("rook", true, true, 'a', 1);
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == "rook");
      assert(chessPieceArray[0]->getIsAlive());
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 1);
      assert(ChessPiece::getAmountOfObjects() == 1);

      chessPieceArray[1] = new ChessPiece("ROOK", false, true, 'H', 8);
      assert(chessPieceArray[1]->getId() == 1);
      assert(chessPieceArray[1]->getType() == "rook");
      assert(chessPieceArray[1]->getIsAlive());
      assert(!chessPieceArray[1]->getIsWhite());
      assert(chessPieceArray[1]->getXPos() == 'h');
      assert(chessPieceArray[1]->getYPos() == 8);
      assert(ChessPiece::getAmountOfObjects() == 2);

      chessPieceArray[0]->movePiece('a', 6);
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == "rook");
      assert(chessPieceArray[0]->getIsAlive());
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 6); // Only this changes
      assert(ChessPiece::getAmountOfObjects() == 2);

      chessPieceArray[0]->killPiece();
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == "rook");
      assert(!chessPieceArray[0]->getIsAlive()); // Only this changes
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 6);
      assert(ChessPiece::getAmountOfObjects() == 2);

      chessPieceArray[2] = new ChessPiece("kInG", true, true, 'd', 3);
      assert(chessPieceArray[2]->getId() == 2);
      assert(chessPieceArray[2]->getType() == "king");
      assert(chessPieceArray[2]->getIsAlive());
      assert(chessPieceArray[2]->getIsWhite());
      assert(chessPieceArray[2]->getXPos() == 'd');
      assert(chessPieceArray[2]->getYPos() == 3);
      assert(ChessPiece::getAmountOfObjects() == 3);
      
      cout << chessPieceArray[2]->toString();
      
      delete chessPieceArray[0];
      assert(ChessPiece::getAmountOfObjects() == 2);
      delete chessPieceArray[1];
      assert(ChessPiece::getAmountOfObjects() == 1);
      delete chessPieceArray[2];
      assert(ChessPiece::getAmountOfObjects() == 0);


      chessPieceArray[3] = new ChessPiece("queef", 5, true, 'd', 3);
      cout << "Foobar\n"; // Shouldn't be reachable
   }
   catch(runtime_error(e)) {
      cout << e.what();
   }
   catch(...) {
      cout << "Unexpected error!\n";
   }

   return 0;
}