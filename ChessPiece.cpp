#include <iostream>
#include <exception>
#include <stdexcept>
#include <cctype>

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

   ~ChessPiece() {
      --amountOfObjects;
   }
   
   static int getAmountOfObjects() {
      return amountOfObjects;
   }
   
   int getId() {
      return id;
   }
   
   string getType(string type) const {
      return type;
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
         throw(runtime_error("Invalid input.\n"));
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
         throw(runtime_error("Invalid input.\n"));
      }
   } 
   
   void setYPos(int yPos) {
      // (yPos > 0 && yPos < 9) ? this->yPos = yPos : throw(runtime_error("Invalid input.\n"));
      if(yPos > 0 && yPos < 9) {
         this->yPos = yPos;
      }
      else {
         throw(runtime_error("Invalid input.\n"));
      }
   }

   public:
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
      cout << chessPieceArray[0]->toString();
      cout << ChessPiece::getAmountOfObjects() << "\n";


      chessPieceArray[1] = new ChessPiece("ROOK", false, true, 'H', 8);
      cout << chessPieceArray[1]->toString();
      cout << ChessPiece::getAmountOfObjects() << "\n";

      chessPieceArray[0]->movePiece('a', 6);
      cout << chessPieceArray[0]->toString();

      chessPieceArray[0]->killPiece();
      cout << chessPieceArray[0]->toString();
      
      delete chessPieceArray[0];
      cout << chessPieceArray[0]->toString();

   }
   catch(runtime_error(e)) {
      cout << e.what();
   }
   catch(...) {
      cout << "Unexpected error!\n";
   }

   return 0;
}