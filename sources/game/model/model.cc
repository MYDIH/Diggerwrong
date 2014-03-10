#include "GameModel.hh"

#include <cstdlib>

using namespace diggewrong;

GameModel::GameModel(unsigned width, unsigned height, double difficulty
		     ,unsigned atarget, unsigned alifes)

   :board(width*height)
   ,target(atarget)
   ,lifes(alifes)
{
   fillBoard(difficulty);
}

void GameModel::fillBoard(double difficulty)
{
   for (square::Square* & square : board)
   {
      square = newRandomSquare(difficulty);
   }
}

square::Square* GameModel::newRandomSquare(double difficulty)
{
   double r = rand() / (double) RAND_MAX;

   double pbomb  = difficulty * 0.7;
   double pbonus = (1 - pbomb) * 0.2;

   if      (r <= pbomb)          return new square::Square(difficulty); // bomb
   else if (r <= pbomb + pbonus) return new square::Square(difficulty); // bonus
   else                          return new square::Square(difficulty); // bonus
}
