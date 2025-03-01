#include <iostream>
#include <exception>
#include <stdexcept>
#include <cctype>
#include <assert.h>

#define ARRAY_SIZE 5

using namespace std;

enum pieceType {
   PAWN,
   KNIGHT,
   BISHOP,
   ROOK,
   QUEEN,
   KING
};

class ChessPiece {
   public:
   static int amount_Of_Objects;
   static int ID;
   int id;
   const enum pieceType type;
   const bool isWhite;
   bool isAlive;
   char xPos;
   int yPos;

   ChessPiece(enum pieceType type, bool isWhite) 
      : id(ID++), 
      type(type), 
      isWhite(isWhite)
   {  
      setIsAlive(false);
      ++amount_Of_Objects;
   }

   ChessPiece(enum pieceType type, bool isWhite, char xPos, int yPos) 
      : id(ID++), 
      type(type), 
      isWhite(isWhite) 
   {
      setIsAlive(true);
      setXPos(xPos);
      setYPos(yPos);
      ++amount_Of_Objects;
   }
   
   ~ChessPiece() {
      --amount_Of_Objects;
   }
   
   private:
   void setIsAlive(bool isAlive) {
      this->isAlive = isAlive;
   }
   
   void setXPos(char xPos) {
      xPos = tolower(xPos);
      if(xPos >= 'a' && xPos <= 'h') {
         this->xPos = xPos;
      }
      else {
         throw(runtime_error("Error. Invalid X position value.\n"));
      }
   } 
   
   void setYPos(int yPos) {
      if(yPos > 0 && yPos < 9) {
         this->yPos = yPos;
      }
      else {
         throw(runtime_error("Error. Invalid Y position value.\n"));
      }
   }

   public:
   static int getAmount_Of_Objects() {
      return amount_Of_Objects;
   }
   
   int getId() {
      return id;
   }
   
   enum pieceType getType() const {
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
   
   void kill() {
      setIsAlive(false);
   }
   
   void move(char xPos, int yPos) {
      if(isAlive) {
         setXPos(xPos);
         setYPos(yPos);
      }
      else {
         throw runtime_error("Error. Can't change coordinates of a dead chess piece.\n");
      }
   }
};

int ChessPiece::amount_Of_Objects = 0;
int ChessPiece::ID = 0;

void deleteArray(ChessPiece **array) {
   int size = ChessPiece::getAmount_Of_Objects();
   for (int i = 0; i < size; ++i) {
      delete array[i];
   }
}

int main() {
   
   ChessPiece *chessPieceArray[ARRAY_SIZE];

   try {

      chessPieceArray[0] = new ChessPiece(ROOK, true, 'a', 1);
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == ROOK);
      assert(chessPieceArray[0]->getIsAlive());
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 1);
      assert(ChessPiece::getAmount_Of_Objects() == 1);

      chessPieceArray[1] = new ChessPiece(ROOK, false, 'H', 8);
      assert(chessPieceArray[1]->getId() == 1);
      assert(chessPieceArray[1]->getType() == ROOK);
      assert(chessPieceArray[1]->getIsAlive());
      assert(!chessPieceArray[1]->getIsWhite());
      assert(chessPieceArray[1]->getXPos() == 'h');
      assert(chessPieceArray[1]->getYPos() == 8);
      assert(ChessPiece::getAmount_Of_Objects() == 2);

      chessPieceArray[0]->move('a', 6);
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == ROOK);
      assert(chessPieceArray[0]->getIsAlive());
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 6); // Only this changes
      assert(ChessPiece::getAmount_Of_Objects() == 2);

      chessPieceArray[0]->kill();
      assert(chessPieceArray[0]->getId() == 0);
      assert(chessPieceArray[0]->getType() == ROOK);
      assert(!chessPieceArray[0]->getIsAlive()); // Only this changes
      assert(chessPieceArray[0]->getIsWhite());
      assert(chessPieceArray[0]->getXPos() == 'a');
      assert(chessPieceArray[0]->getYPos() == 6);
      assert(ChessPiece::getAmount_Of_Objects() == 2);

      chessPieceArray[2] = new ChessPiece(KING, true, 'd', 3);
      assert(chessPieceArray[2]->getId() == 2);
      assert(chessPieceArray[2]->getType() == KING);
      assert(chessPieceArray[2]->getIsAlive());
      assert(chessPieceArray[2]->getIsWhite());
      assert(chessPieceArray[2]->getXPos() == 'd');
      assert(chessPieceArray[2]->getYPos() == 3);
      assert(ChessPiece::getAmount_Of_Objects() == 3);

      chessPieceArray[3] = new ChessPiece(KNIGHT, true);
      assert(chessPieceArray[3]->getId() == 3);
      assert(chessPieceArray[3]->getType() == KNIGHT);
      assert(!(chessPieceArray[3]->getIsAlive()));
      assert(chessPieceArray[3]->getIsWhite());
      assert(ChessPiece::getAmount_Of_Objects() == 4);

      chessPieceArray[4] = new ChessPiece(QUEEN, true, 'k', 87);
      cout << "Foobar\n"; // Shouldn't be reachable

      deleteArray(chessPieceArray);
   }
   catch(runtime_error(e)) {
      cout << e.what();
      deleteArray(chessPieceArray);
   }
   catch(...) {
      cout << "Unexpected error!\n";
      deleteArray(chessPieceArray);
   }

   assert(ChessPiece::getAmount_Of_Objects() == 0);

   return 0;
}