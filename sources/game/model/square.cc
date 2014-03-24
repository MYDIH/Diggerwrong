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
      delete this;
   else
      Retain_count--;
}

Square::~Square()
{}

//
// Digged
//

bool Digged::dig(GameModel & m, int x, int y, int dx, int dy, int distance)
{ return true; }

const std::string Digged::toString() const
{ return "   "; }

Square* Digged::clone()
{ return new Digged; }

//
// Normal
//

Normal::Normal()
{}

Normal::Normal(double difficulty, unsigned longestside)
{
   const double r = rand() / (double) RAND_MAX;

   const double max = longestside * 0.7 * difficulty + longestside * 0.2;

   Value = max*r + 1;
}

Normal::Normal(const Normal & other)
{ Value = other.Value; }

const std::string Normal::toString() const
{ return ' ' + GameModel::intToString(Value) + ' '; }

bool Normal::dig(GameModel & m, int x, int y, int dx, int dy, int distance)
{
   // si distance < 0, on est la première case visité du tour, on lance donc le déplacement
   if(distance < 0)
   {
        distance = Value - 1;
        Square * tempDigged = new Digged;
        m.replaceSquare(x - dx, y - dy, tempDigged);
   }

   Square * digged = new Digged;
   m.replaceSquare(x, y, digged);

   if (distance > 0 and (dx != 0 or dy != 0))
      return m.digAt(x + dx, y + dy, dx, dy, distance - 1);
   else return false;
}

Square* Normal::clone()
{ return new Normal(*this); }

//
// Bonus
//

Bonus::Bonus(double difficulty, unsigned longestside)
   : Normal(difficulty, longestside)
{
   const double plife  = (1.1 - difficulty) * 0.2;

   const double r = rand() / (double) RAND_MAX;

   if (r <= plife)
   {
      Lifes = 1;
      Score = 0;
   }
   else
   {
      const double r = rand() / (double) RAND_MAX;

      Score = (100 * r + 10);
   }
}

Bonus::Bonus(const Bonus & other)
{
    Lifes = other.Lifes;
    Score = other.Score;
    Value = other.Value;
}

bool Bonus::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   m.addBonusScore(Score);
   m.addBonusLifes(Lifes);

   return Normal::dig(m,x,y,dx,dy,distance);
}

const std::string Bonus::toString() const
{
   return '{' + GameModel::intToString(Value) + '}';
}

Square* Bonus::clone()
{ return new Bonus(*this); }

//
// Bomb
//

bool Bomb::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   return true;
}

const std::string Bomb::toString() const
{ return " * "; }

Square* Bomb::clone()
{ return new Bomb; }






