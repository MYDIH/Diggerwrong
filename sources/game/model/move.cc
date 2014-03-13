#include "GameModel.hh"

using namespace diggewrong;

bool GameModel::move(char dx, char dy)
{
   unsigned distance = Board[Digger.x + dx][Digger.y + dy] -> distance();

   while (distance > 0)
   {
      Digger.x += dx;
      Digger.y += dy;

      unsigned score, time, lifes;
      Board[Digger.x][Digger.y] -> dig();

      distance--;
      Reached++;
   }



   return true;
}




