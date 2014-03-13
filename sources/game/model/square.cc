#include "GameModel.hh"

using namespace diggewrong;


square::Square::Square(double difficulty)
{
}

square::Square::~Square()
{
}

unsigned square::Square::distance() const
{
   return 2;
}

bool square::Square::dig(unsigned & score, unsigned & time, unsigned & lifes) const
{
   score = 1;
   time  = 1;
   lifes = 1;

   return true;
}




