#include "GameSquare.hh"

using namespace diggewrong;

//
// Square
//


void Square::retain()
{
   Retain_count++;
}

void Square::release()
{
   if (Retain_count == 1)
   {
      delete this;
   }
   else
   {
      Retain_count--;
   }
}

Square::~Square()
{}

int Square::value() const
{
   return -1;
}

//
// Digged
//

bool Digged::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   return true;
}

const std::string & Digged::type() const
{
   return Type;
}

const std::string Digged::toString() const
{ return "   "; }

//
// Normal
//

Normal::Normal(double difficulty, unsigned longestside)
{
   const double r = rand() / (double) RAND_MAX;

   const double max = (longestside/3.0)*r + (longestside/5.0);

   Value = max*difficulty + 1;
}

int Normal::value() const
{
   return Value;
}

const std::string & Normal::type() const
{
   return Type;
}

const std::string Normal::toString() const
{ return ' ' + GameModel::intToString(value()) + ' '; }

bool Normal::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   // si distance < 0, on est la première case visité du tour, on lance donc le déplacement
   distance = (distance < 0) ? Value - 1 : distance;


   Square * digged = new Normal(12,12);
   m.replaceSquare(x,y, digged);
   digged -> release();

   m.addScore(Value*10);

   if (distance > 0 and (dx != 0 or dy != 0))
   {
      return m.digAt(x + dx, y + dy, dx, dy, distance - 1);
   }
   else return false;
}



//
// Bonus
//


bool Bomb::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   return true;
}

const std::string & Bomb::type() const
{
   return Type;
}

const std::string Bomb::toString() const
{ return " * "; }






