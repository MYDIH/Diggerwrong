#include "GameModel.hh"

#include <cstdlib>

using namespace diggewrong;

GameModel::GameModel(unsigned width, unsigned height, double difficulty
		     ,unsigned target, unsigned lifes, unsigned timelimit)

   :Board(width*height)

   ,Target(target)
   ,Reached(0)

   ,Score(0)
   ,Lifes(lifes)
   ,Timelimit(timelimit)
   
   ,Bonus_score(0)
   ,Bonus_lifes(0)
   ,Bonus_time(0)
{
   fillBoard(difficulty);
}

void GameModel::fillBoard(double difficulty)
{
   for (square::Square* & square : Board)
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


