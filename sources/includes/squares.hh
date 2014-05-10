#pragma once

#include "Square.hh"
#include "SquareView.hh"



class SNormal : public Square
{
protected:
   unsigned Value;

public:
   SNormal(unsigned val);
   SNormal(double difficulty, unsigned longestside);
   SNormal(const SNormal & other);

   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};
class Normal : public SNormal, public AnimatedSquareView
{};



class SBonus : public SNormal
{
private:
   unsigned Lifes;
   unsigned Score;

public:
   SBonus(unsigned val, unsigned life, unsigned score);
   SBonus(double difficulty, unsigned longestside);
   SBonus(const SBonus & other);

   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};
class Bonus : public SBonus, public AnimatedSquareView
{};



class SDigged : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};
class Digged : public SDigged, public AnimatedSquareView
{};



class SBomb : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
   Square * clone() override;
};
class Bomb : public SBomb, public AnimatedSquareView
{};





