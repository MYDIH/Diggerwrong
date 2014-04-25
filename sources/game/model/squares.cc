#include "Square.hh"


//
// Digged
//

bool Digged::dig(GameModel & m, int x, int y, int dx, int dy, int distance)
{ return true; }

const std::string Digged::toString(const int &charSet) const
{ return "   "; }

Square* Digged::clone()
{ return new Digged; }


//
// Normal
//

Normal::Normal(unsigned val)
{ Value = val; }

Normal::Normal(double difficulty, unsigned longestside)
{
   const double r = rand() / (double) RAND_MAX;

   const double max = longestside * 0.7 * difficulty + longestside * 0.2;

   Value = max*r + 1;
}

Normal::Normal(const Normal & other)
{ Value = other.Value; }

const std::string Normal::toString(const int &charSet) const
{ return CHARS[charSet][7] + GameModel::intToString(Value) + CHARS[charSet][8]; }

bool Normal::dig(GameModel & m, int x, int y, int dx, int dy, int distance)
{
  m.addScore(Value*10);

   // si distance < 0, on est la première case visité du tour, on lance donc le déplacement
   if(distance < 0)
   {
        distance = Value - 1;
   }

   Square * digged = new Digged;
   m.replaceSquare(x, y, digged);
   digged -> release();

   if (distance > 0 and (dx != 0 or dy != 0))
     return m.digAt(x + dx, y + dy, dx, dy, distance - 1);
   else return false;
}

Square* Normal::clone()
{ return new Normal(*this); }


//
// Bonus
//

Bonus::Bonus(unsigned val, unsigned life, unsigned score) : Normal(val)
{
    Lifes = life;
    Score = score;
}

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

Bonus::Bonus(const Bonus & other) : Normal(other)
{
    Lifes = other.Lifes;
    Score = other.Score;
}

bool Bonus::dig(GameModel & m, int x, int y
		 ,int dx, int dy, int distance)
{
   m.addBonusScore(Score);
   m.addBonusLifes(Lifes);

   return Normal::dig(m,x,y,dx,dy,distance);
}

const std::string Bonus::toString(const int &charSet) const
{
   return CHARS[charSet][1] + GameModel::intToString(Value) + CHARS[charSet][2];
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

const std::string Bomb::toString(const int &charSet) const
{ return CHARS[charSet][0]; }

Square* Bomb::clone()
{ return new Bomb; }






