#include "Board.hh"
#include "consts.hh"
#include "squares.hh"
#include "Square.hh"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <iostream> // debug


void Board::Observer::push(const Board::change& c)
{
   if ( care(c) )
      Changes.push(c);
}
bool Board::Observer::care(const Board::change& c)
{ return true; }
void Board::Observer::pop()
{ 
   if (Changes.size() > 0)
      Changes.pop();
}
const Board::change * Board::Observer::front()
{
   if (Changes.size() > 0)
      return &Changes.front();
   else
      return nullptr;
}

Board::Board(unsigned width, unsigned height, double difficulty
	     ,unsigned target)


   :Squares(width)

   ,Digger({width/2, height/2})

   ,Target(target)
   ,Reached(0)

   ,Score(0)
    //,Lifes(lifes)
    //,Timelimit(timelimit)

   ,Bonus_score(0)
   ,Bonus_lifes(0)
    //,Bonus_time(0)

   ,State(CONTINUE)
{
   const unsigned longestside = (width > height) ? width : height;

    for (auto & column : Squares)
    {
        column.resize(height);

        for (auto & square : column)
        {
	   square = newRandomSquare(difficulty, longestside);
        }
    }

   Square * tmp = new Digged;
   replaceSquare(Digger.x, Digger.y, tmp);
   tmp -> release();
}

void Board::releaseSquares()
{
   for(unsigned i = 0; i<Squares.size(); i++)
      for(unsigned j = 0; j<Squares[0].size(); j++)
	 Squares[i][j]->release();
}

void Board::copySquares(const Board &m)
{
   Squares.resize(m.Squares.size());

   for(unsigned i = 0; i<m.Squares.size(); i++)
   {
      Squares[i].resize(m.Squares[0].size());

      for(unsigned j = 0; j<m.Squares[0].size(); j++)
	 Squares[i][j] = m.Squares[i][j] -> clone();
   }
}

Board::Board(const Board &m)
{
   operator=(m);
}

const Board & Board::operator=(const Board &m)
{
   Digger = m.Digger;

   Target = m.Target;
   Reached = m.Reached;

   Score = m.Score;

   Bonus_score = m.Bonus_score;
   Bonus_lifes = m.Bonus_lifes;

   State = m.State;

   releaseSquares();
   copySquares(m);

   return *this;
}


Board::~Board()
{
   notify( {change::DESTRUCT} );
   releaseSquares();
}

GameState Board::move(int dx, int dy)
{
   if (State == CONTINUE)
   {
      if (dx > 0) dx = 1;
      else if (dx < 0) dx = -1;

      if (dy > 0) dy = 1;
      else if (dy < 0) dy = -1;

      if ( digAt(Digger.x + dx, Digger.y + dy, dx, dy) )
      {
	 State = LOST;
	 notify( {change::LOST, {Digger.x,Digger.y}} );
      }
      else if (Reached >= Target)
      {
	 State = WON;


	 change c = {change::WON, {Digger.x,Digger.y}};
	 c.infos.value = {Reached-Target, Reached};
	 notify( c );
      }
   }

   return State;
}

// temporaire ; devra être indépendant de Board
Square* Board::newRandomSquare(double difficulty, unsigned longestside)
{
   double r = rand() / (double) RAND_MAX;

   double pbomb  = difficulty * 0.12;
   double pbonus = (1-difficulty) * 0.017;

   if      (r <= pbomb)          return new Bomb(); // bomb
   else if (r <= pbomb + pbonus) return new Bonus(difficulty, longestside); // bonus
   else                          return new Normal(difficulty, longestside); // normal
}

const std::string Board::toString(const int &charSet) const
{
   std::string tempString = "";
   std::string tempLine = "";

   tempLine += CHARS[charSet][4];
   for(unsigned i=0; i<Squares[0].size(); i++)
      tempLine += "----";
   tempLine.pop_back();
   tempLine += CHARS[charSet][5];

   for(unsigned i=0; i<Squares.size(); i++)
   {
      for(unsigned j=0; j<Squares[i].size(); j++)
      {
	 if(i == 0 && j == 0)
	    tempString += tempLine + '\n';
	 tempString += CHARS[charSet][6];
	 if(i == Digger.x && j == Digger.y)
	    tempString += CHARS[charSet][3];
	 else
	    tempString += Squares[i][j]->toString(charSet);
	 if(j == Squares[i].size() - 1)
	    tempString += CHARS[charSet][6];
      }
      tempString += '\n';
      if(i == Squares.size() - 1)
	 tempString += tempLine;
   }

   return tempString;
}

bool Board::isOutOfRange(int x, int y) const
{
   if (x >= 0 and y >= 0 and (unsigned)x < Squares.size() and (unsigned)y < Squares[0].size())
      return false;
   else
      return true;
}

bool Board::digAt(int x, int y, int dx, int dy, int distance)
{
   if (isOutOfRange(x,y))
   {
      return true;
   }
   else
   {
      Square * square = Squares[x][y];

      Digger.x = x;
      Digger.y = y;
      Reached++;

      change c = {change::MOVE, {Digger.x,Digger.y}};
      c.infos.value = {1,Reached};
      notify( c );

      square -> retain(); // on retarde l'éventuelle désallocation de la case pour garentir la bonne execution de dig()
      const bool ret = square -> dig(*this,x,y,dx,dy,distance);
      square -> release();

      return ret;
   }
}

void Board::addScore(unsigned score)
{
   Score += score;

   change c = {change::SCORE, {Digger.x, Digger.y}};
   c.infos.value = {score, Score};
   notify( c );
}

void Board::addBonusScore(unsigned score)
{
   Bonus_score += score;

   change c = {change::SCORE_BONUS, {Digger.x, Digger.y}};
   c.infos.value = {score, Bonus_score};
   notify( c );
}

void Board::addBonusLifes(unsigned lifes)
{
   Bonus_lifes += lifes;

   change c = {change::LIFE_BONUS, {Digger.x, Digger.y}};
   c.infos.value = {lifes, Bonus_lifes};
   notify( c );
}


void Board::replaceSquare(int x, int y, Square * newone)
{
   if (not isOutOfRange(x,y))
   {
      Squares[x][y] -> release();

      newone -> retain();
      Squares[x][y] = newone;

      change c = {change::REPLACE, {(unsigned)x,(unsigned)y}};
      c.infos.square = newone;
      notify( c );
   }
}

// Accesseurs :

unsigned Board::getTarget() const
{ return Target; }

unsigned Board::getReached() const
{ return Reached; }

unsigned Board::getScore() const
{ return Score; }

unsigned Board::getWidth()   const
{ return Squares.size(); }

unsigned Board::getHeight()  const
{
   if (Squares.size() < 1)
      return 0;
   else
      return Squares[0].size();
}

point Board::getDigger() const
{ return Digger; }

unsigned Board::getBonusScore() const
{ return Bonus_score; }

unsigned Board::getBonusLifes() const
{ return Bonus_lifes; }

const Square * Board::getSquare(unsigned x, unsigned y) const
{ return Squares[x][y]; }


void Board::registerObserver(Observer* o)
{ Observers.insert(o); }
void Board::unregisterObserver(Observer* o)
{ Observers.erase(o); }
void Board::notify(const change & c) const
{
   for (Observer* o : Observers)
      if (o)
	 o -> push(c);
}
