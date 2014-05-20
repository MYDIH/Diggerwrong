#include "Square.hh"
#include "squares.hh"
#include "Animation.hh"
#include "consts.hh"

#include <cmath>
#include <string>


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Normal
//////
///////////////////////////////////////////
//////////////////////////////////////////
AnimationResource Normal::appearing("normal", "appearing.txt");
AnimationResource Normal::appeared("normal", "appeared.txt");
AnimationResource Normal::disappearing("normal", "disappearing.txt");
FontResource Normal::Font("normal", "font.txt");

void Normal::init(ResourcesPool & pool)
{
   pool.add( &Normal::appearing    );
   pool.add( &Normal::appeared     );
   pool.add( &Normal::disappearing );
   pool.add( &Normal::Font );
}

Square * Normal::create(double difficulty, unsigned width, unsigned height)
{ return new Normal(difficulty, (width > height)? width : height); }

Normal::Normal(double d, unsigned l)
   :SNormal(d,l)
   ,AnimatedSquareView(&appearing,nullptr
		       ,&appeared,nullptr
		       ,&disappearing,nullptr)
   ,Fade_in(1,0,0.3)
   ,Fade_out(0,1,0.2)
{}

Normal::Normal(const Normal& o)
   :SNormal(o)
   ,AnimatedSquareView(o)
   ,Fade_in(1,0,0.3)
   ,Fade_out(0,1,0.2)
{}

Square* Normal::clone() const
{ return new Normal(*this); }


void Normal::draw(sf::RenderTarget & drawer, float now) const
{
   AnimatedSquareView::draw(drawer,now);

   Font.draw_string(drawer, std::to_string(Value)
		    ,-SQUARE_WIDTH/2, -SQUARE_HEIGHT/2
		    ,Fade_in.getValue(now) * Fade_out.getValue(now) );
}

void Normal::appear(float at)
{
   AnimatedSquareView::appear(at);
   Fade_in.start(at + Appearing.remaining_time(at));
}

void Normal::disappear(float at)
{
   AnimatedSquareView::disappear(at);
   Fade_out.start(at);
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
AnimationResource Bonus::appearing("bonus", "appearing.txt");
AnimationResource Bonus::appeared("bonus", "appeared.txt");
AnimationResource Bonus::disappearing("bonus", "disappearing.txt");

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
   ,Fade_in(1,0,0.3)
   ,Fade_out(0,1,0.2)
{}

Bonus::Bonus(const Bonus& o)
   :SBonus(o)
   ,AnimatedSquareView(o)
   ,Fade_in(1,0,0.3)
   ,Fade_out(0,1,0.2)
{}


Square* Bonus::clone() const
{ return new Bonus(*this); }

void Bonus::draw(sf::RenderTarget & drawer, float now) const
{
   AnimatedSquareView::draw(drawer,now);

   Normal::Font.draw_string(drawer, std::to_string(Value)
			    ,-SQUARE_WIDTH/2, -SQUARE_HEIGHT/2
			    ,Fade_in.getValue(now) * Fade_out.getValue(now) );

}

void Bonus::appear(float at)
{
   AnimatedSquareView::appear(at);
   Fade_in.start(at + Appearing.remaining_time(at));
}

void Bonus::disappear(float at)
{
   AnimatedSquareView::disappear(at);
   Fade_out.start(at);
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
AnimationResource Digged::appearing("digged", "appearing.txt");
AnimationResource Digged::appeared("digged", "appeared.txt");

void Digged::init(ResourcesPool & pool)
{
   pool.add( &Digged::appearing );
   pool.add( &Digged::appeared  );
}

Square * Digged::create(double difficulty, unsigned width, unsigned height)
{ return new Digged(); }

Digged::Digged()
   :AnimatedSquareView(&Digged::appearing,nullptr
		       ,&Digged::appeared,nullptr
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
AnimationResource Bomb::appearing("bomb", "appearing.txt");
AnimationResource Bomb::appeared("bomb", "appeared.txt");
AnimationResource Bomb::disappearing("bomb", "disappearing.txt");

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







