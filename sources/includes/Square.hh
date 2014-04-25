#pragma once

#include "Board.hh"
#include "consts.hh"

#include <string>
#include <sstream>


class Board;

/*template<class C>
  C* clone(const C & objectToClone)
  { return new C(objectToClone); }*/

class Square
{
private:
   unsigned Retain_count = 1;

public:
   virtual ~Square();

   virtual bool dig(GameModel & model, int x, int y
		    ,int dx=0, int dy=0, int distance=-1) = 0;

   virtual const std::string toString(const int &charSet) const = 0;
   virtual Square * clone() = 0;

   void retain();
   void release();
};


class Normal : public Square
{
protected:
   unsigned Value;

public:
   Normal(unsigned val);
   Normal(double difficulty, unsigned longestside);
   Normal(const Normal & other);

   const std::string toString(const int &charSet) const override;

   bool dig(GameModel & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};

class Bonus : public Normal
{
private:
   unsigned Lifes;
   unsigned Score;

public:
   Bonus(unsigned val, unsigned life, unsigned score);
   Bonus(double difficulty, unsigned longestside);
   Bonus(const Bonus & other);

   const std::string toString(const int &charSet) const override;

   bool dig(GameModel & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};

class Digged : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(GameModel & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};


class Bomb : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(GameModel & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};






