#include "GameModel.hh"

using namespace diggewrong;

Normal::Normal(double difficulty, unsigned longestside)
{
   const double r = rand() / (double) RAND_MAX;

   const max = (longestside/3.0)*r + (longestside/5.0);

   Value = max*difficulty + 1;
}

int Normal::value() const override
{
   return Value;
}

const string & Normal::type() const override
{
   return Type;
}

void Normal::dig(unsigned dx, unsigned dy, int distance
		 ,GameModel & m, unsigned x, unsigned y) override
{
   // si distance < 0, on est la première case visité du tour, on lance donc le déplacement
   const int distance = (distance < 0) ? Value - 1 : distance;


   if (distance > 0 and m.isOutOfRange(x + dx, y + dy))
   {
      m.die();
   }
   else
   {
      m.replaceSquare(x,y, new Digged());
      m.addScore(Value*10);

      // -- suicide
      delete this;
      // --

      if (distance > 0)
      {
	 m.digAt(x + dx, y + dy, dx, dy, distance - 1);
      }
   }
}




