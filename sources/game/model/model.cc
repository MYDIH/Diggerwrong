#include "GameModel.hh"

#include <cstdlib>

using namespace diggewrong;

GameModel::GameModel(unsigned width, unsigned height, double difficulty
		     ,unsigned target, unsigned lifes, unsigned timelimit)

   :Board(width)

   ,Digger({width/2, height/2})

   ,Target(target)
   ,Reached(0)

   ,Score(0)
   ,Lifes(lifes)
    //,Timelimit(timelimit)
   
   ,Bonus_score(0)
   ,Bonus_lifes(0)
    //,Bonus_time(0)
{
   for (auto & column : Board)
   {
      column.resize(width);

      for (auto & square : column)
      {
	 square = newRandomSquare(difficulty);
      }
   }

   //square = newRandomSquare(difficulty);
}

GameModel::~GameModel()
{
   for (auto & column : Board)
   {
      for (auto & square : column)
      {
	 delete square;
      }
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


