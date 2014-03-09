#include "GameModel.hh"

using namespace diggewrong;

GameModel::GameModel(unsigned width, unsigned height) : board(width*height)
{
   for (square::Square* & square : board)
   {
      square = newRandomSquare(0.5);
   }
}

square::Square* GameModel::newRandomSquare(double difficulty)
{
   return nullptr;
}
