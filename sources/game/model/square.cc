#include "GameModel.hh"

using namespace diggewrong;


square::Square::Square(double difficulty)
{
}

unsigned square::Square::distance()
{
   return 2;
}

bool square::Square::dig(unsigned & score, unsigned & time, unsigned & lifes)
{
   score = 1;
   time  = 1;
   lifes = 1;

   return true;
}




