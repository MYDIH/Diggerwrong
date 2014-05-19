#include "Square.hh"
#include "squares.hh"

#include <cmath>


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Normal
//////
///////////////////////////////////////////
//////////////////////////////////////////
AnimationResource Normal::appearing("normal/ap");
AnimationResource Normal::appeared("normal/loop");
AnimationResource Normal::disappearing("normal/disap");

void Normal::init(ResourcesPool & pool)
{
   pool.add( &Normal::appearing    );
   pool.add( &Normal::appeared     );
   pool.add( &Normal::disappearing );
}

Square * Normal::create(double difficulty, unsigned width, unsigned height)
{ return new Normal(difficulty, (width > height)? width : height); }

Normal::Normal(double d, unsigned l)
   :SNormal(d,l)
   ,AnimatedSquareView(&Normal::appearing,nullptr
		       ,&Normal::appeared,nullptr
		       ,&Normal::disappearing,nullptr)
{}

Normal::Normal(const Normal& o)
   :SNormal(o)
   ,AnimatedSquareView(o)
{}

Square* Normal::clone() const
{ return new Normal(*this); }


void Normal::draw(sf::RenderTarget & drawer, float now) const
{
   AnimatedSquareView::draw(drawer,now);
}

SNormal::SNormal(unsigned val)
{ Value = val; }

SNormal::SNormal(double difficulty, unsigned longestside)
{
   const double r = pow(rand() / (double) RAND_MAX, 1.5);

   const double max = longestside * 0.3 * difficulty + longestside * 0.2;

   Value = max*r + 1;
}

SNormal::SNormal(const SNormal & other)
{ Value = other.Value; }

const std::string SNormal::toString(const int &charSet) const
{
   const std::string ret = CHARS[charSet][7] + typeToString<int>(Value);

   if (Value < 10)
      return ' ' + ret + ' ';
   else if (Value < 100)
      return ' ' + ret;
   else
      return ret;
}

bool SNormal::dig(Board & m, int x, int y, int dx, int dy, int distance)
{
   m.addScore(Value*10);

   // si distance < 0, on est la première case visité du tour, on lance donc le déplacement
   if(distance < 0)
   {
      distance = Value - 1;
   }

   Square * tmp = new Digged();
   m.replaceSquare(x, y, tmp);
   tmp -> release();

   if (distance > 0 and (dx != 0 or dy != 0))
      return m.digAt(x + dx, y + dy, dx, dy, distance - 1);
   else
      return false;
}


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Bonus
//////
///////////////////////////////////////////
///////////////////////////////////////////
AnimationResource Bonus::appearing("bonus/ap");
AnimationResource Bonus::appeared("bonus/loop");
AnimationResource Bonus::disappearing("bonus/disap");

void Bonus::init(ResourcesPool & pool)
{
   pool.add( &Bonus::appearing );
   pool.add( &Bonus::appeared );
   pool.add( &Bonus::disappearing );
}

Square * Bonus::create(double difficulty, unsigned width, unsigned height)
{ return new Bonus(difficulty, (width > height) ? width : height); }

Bonus::Bonus(double d, unsigned l)
   :SBonus(d,l)
   ,AnimatedSquareView(&Bonus::appearing,nullptr
		       ,&Bonus::appeared,nullptr
		       ,&Bonus::disappearing,nullptr)
{}

Bonus::Bonus(const Bonus& o)
   :SBonus(o)
   ,AnimatedSquareView(o)
{}


Square* Bonus::clone() const
{ return new Bonus(*this); }

void Bonus::draw(sf::RenderTarget & drawer, float now) const
{
   AnimatedSquareView::draw(drawer,now);
}

SBonus::SBonus(unsigned val, unsigned life, unsigned score) : SNormal(val)
{
   Lifes = life;
   Score = score;
}

SBonus::SBonus(double difficulty, unsigned longestside)
   : SNormal(difficulty, longestside)
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

SBonus::SBonus(const SBonus & other) : SNormal(other)
{
   Lifes = other.Lifes;
   Score = other.Score;
}

bool SBonus::dig(Board & m, int x, int y
		 ,int dx, int dy, int distance)
{
   m.addBonusScore(Score);
   m.addBonusLifes(Lifes);

   return SNormal::dig(m,x,y,dx,dy,distance);
}

const std::string SBonus::toString(const int &charSet) const
{
   if (Value < 10)
      return CHARS[charSet][1] + typeToString<int>(Value) + CHARS[charSet][2];
   else
      return CHARS[charSet][1] + typeToString<int>(Value);

}


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Digged
//////
///////////////////////////////////////////
///////////////////////////////////////////
AnimationResource Digged::appeared(60,30,true);

void Digged::init(ResourcesPool & pool)
{
   pool.add( &Digged::appeared );
}

Square * Digged::create(double difficulty, unsigned width, unsigned height)
{ return new Digged(); }

Digged::Digged()
   :AnimatedSquareView(nullptr,nullptr
		       ,nullptr,nullptr//&Digged::appeared,nullptr
		       ,nullptr,nullptr)
{}

Square* Digged::clone() const
{ return new Digged(*this); }

bool SDigged::dig(Board & m, int x, int y, int dx, int dy, int distance)
{ return true; }

const std::string SDigged::toString(const int &charSet) const
{ return "   "; }




///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Bomb
//////
///////////////////////////////////////////
///////////////////////////////////////////
AnimationResource Bomb::appearing("bomb/ap");
AnimationResource Bomb::appeared("bomb/loop");
AnimationResource Bomb::disappearing("bomb/disap");

void Bomb::init(ResourcesPool & pool)
{
   pool.add( &Bomb::appearing );
   pool.add( &Bomb::appeared );
   pool.add( &Bomb::disappearing );
}

Square * Bomb::create(double difficulty, unsigned width, unsigned height)
{ return new Bomb(); }

Bomb::Bomb()
   :AnimatedSquareView(&Bomb::appearing,nullptr
		       ,&Bomb::appeared,nullptr//&Bomb::appeared,nullptr
		       ,&Bomb::disappearing,nullptr)
{}


Square * Bomb::clone() const
{ return new Bomb(*this); }

bool SBomb::dig(Board & m, int x, int y
		,int dx, int dy, int distance)
{
   return true;
}

const std::string SBomb::toString(const int &charSet) const
{ return CHARS[charSet][0]; }







