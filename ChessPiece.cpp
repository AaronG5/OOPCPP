#include <iostream>

using namespace std;

class ChessPiece {
   private:
   const string type;
   const bool isWhite;
   bool isAlive;
   char xPos;
   int yPos;

   public:
   ChessPiece(string type, bool isWhite, bool isAlive, char xPos, int yPos) : 
      type(type),
      isWhite(isWhite), 
      isAlive(isAlive), 
      xPos(xPos), 
      yPos(yPos) {}

};

int main() {

   ChessPiece rook = ChessPiece("rook", true, true, 'a', 1);

   return 0;
}