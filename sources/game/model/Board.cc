#include "Board.hh"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Constantes.hh"

#include <iostream> // debug


Board::Board(unsigned width, unsigned height, double difficulty
                     ,unsigned target)


   :Board(width)

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

   for (auto & column : Board)
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

Board::Board(const Board &m) : Board(m.Board.size())
{
    for(unsigned i = 0; i<m.Board.size(); i++)
    {
        Board[i].resize(m.Board[0].size());

        for(unsigned j = 0; j<m.Board[0].size(); j++)
        {
            Board[i][j] = m.Board[i][j]->clone();
        }
    }

    Digger = m.Digger;
    Target = m.Target;
    Reached = m.Reached;
    Score = m.Score;
    Bonus_score = m.Bonus_score;
    Bonus_lifes = m.Bonus_lifes;
}

Board::~Board()
{
   for (auto & column : Board)
   {
      for (auto & square : column)
      {
        square -> release();
      }
   }
}


GameState Board::move(int dx, int dy)
{
    if (State == CONTINUE)
    {
        if ( digAt(Digger.x + dx, Digger.y + dy, dx, dy) )
        {
            State = LOST;
        }
        else if (Reached >= Target)
        {
            State = WON;
        }
    }

    return State;
}

Square* Board::newRandomSquare(double difficulty, unsigned longestside)
{
   double r = rand() / (double) RAND_MAX;

   double pbomb  = difficulty * 0.2;
   double pbonus = (1 - pbomb) * 0.02;

   if      (r <= pbomb)          return new Bomb(); // bomb
   else if (r <= pbomb + pbonus) return new Bonus(difficulty, longestside); // bonus
   else                          return new Normal(difficulty, longestside); // normal
}

const std::string Board::toString(const int &charSet) const
{
    std::string tempString = "";
    std::string tempLine = "";

    tempLine += CHARS[charSet][4];
    for(unsigned i=0; i<Board[0].size(); i++)
        tempLine += "----";
    tempLine.pop_back();
    tempLine += CHARS[charSet][5];

    for(unsigned i=0; i<Board.size(); i++)
    {
        for(unsigned j=0; j<Board[i].size(); j++)
        {
            if(i == 0 && j == 0)
                tempString += tempLine + '\n';
            tempString += CHARS[charSet][6];
            if(i == Digger.x && j == Digger.y)
                tempString += CHARS[charSet][3];
            else
                tempString += Board[i][j]->toString(charSet);
            if(j == Board[i].size() - 1)
                tempString += CHARS[charSet][6];
        }
        tempString += '\n';
        if(i == Board.size() - 1)
        tempString += tempLine;
    }

    return tempString;
}

std::string Board::intToString(const int &e)
{
   std::ostringstream stream;
   stream << e;

   return stream.str();
}

bool Board::isOutOfRange(int x, int y) const
{
   if (x >= 0 and y >= 0 and (unsigned)x < Board.size() and (unsigned)y < Board[0].size())
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
      Square * square = Board[x][y];

      Digger.x = x;
      Digger.y = y;
      Reached++;

      square -> retain();
      const bool ret = square -> dig(*this,x,y,dx,dy,distance);
      square -> release();

      return ret;
   }
}

void Board::addScore(unsigned score)
{
  Score += score;
}

void Board::addBonusScore(unsigned score)
{
   Bonus_score += score;
}

void Board::addBonusLifes(unsigned lifes)
{
   Bonus_lifes += lifes;
}


void Board::replaceSquare(int x, int y, Square * newone)
{
   if (not isOutOfRange(x,y))
   {
      Board[x][y] -> release();
      newone -> retain();

      Board[x][y] = newone;
   }
}

// Accesseurs :

unsigned Board::getTarget() const
{ return Target; }

unsigned Board::getReached() const
{ return Reached; }

unsigned Board::getScore() const
{ return Score; }

