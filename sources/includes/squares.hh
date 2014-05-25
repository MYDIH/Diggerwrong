#pragma once

#include "Square.hh"
#include "SquareView.hh"
#include "resources.hh"
#include "Animation.hh"


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Normal
//////
///////////////////////////////////////////
///////////////////////////////////////////
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

};

class Normal : public SNormal, public AnimatedSquareView
{
private:
   static AnimationResource appearing;
   static AnimationResource appeared;
   static AnimationResource disappearing;

   AnimatedValue Fade_in;
   AnimatedValue Fade_out;

public:
   static FontResource Font;
   static void init(ResourcesPool & pool);
   static Square * create(double difficulty, unsigned width, unsigned height);

   Normal(unsigned);
   Normal(double, unsigned);

   Normal(const Normal &);
   Square * clone() const override;
   
   void draw(sf::RenderTarget & drawer, float now) const override;
   void appear(float at)    override;
   void disappear(float at) override;
   void show(float at)      override;
   void hide(float at)      override;

};



///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Bonus
//////
///////////////////////////////////////////
///////////////////////////////////////////
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
};

class Bonus : public SBonus, public AnimatedSquareView
{
private:
   static AnimationResource appearing;
   static AnimationResource appeared;
   static AnimationResource disappearing;

   AnimatedValue Fade_in;
   AnimatedValue Fade_out;


public:
   static void init(ResourcesPool & pool);
   static Square * create(double difficulty, unsigned width, unsigned height);

   Bonus(double, unsigned);

   Bonus(const Bonus &);
   Square * clone() const override;
   
   void draw(sf::RenderTarget & drawer, float now) const override;
   void appear(float at)    override;
   void disappear(float at) override;
   void show(float at)      override;
   void hide(float at)      override;

};


///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Digged
//////
///////////////////////////////////////////
///////////////////////////////////////////
class SDigged : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
};

class Digged : public SDigged, public AnimatedSquareView
{
private:
   static AnimationResource appearing;
   static AnimationResource appeared;

public:
   static void init(ResourcesPool & pool);
   static Square * create(double difficulty, unsigned width, unsigned height);

   Digged();

   Square * clone() const override;
};



///////////////////////////////////////////
///////////////////////////////////////////
//////
//////   Bomb
//////
///////////////////////////////////////////
///////////////////////////////////////////
class SBomb : public Square
{
public:
   const std::string toString(const int &charSet) const override;

   bool dig(Board & model, int x, int y
	    ,int dx, int dy, int distance) override;
};

class Bomb : public SBomb, public AnimatedSquareView
{
private:
   static AnimationResource appearing;
   static AnimationResource appeared;
   static AnimationResource disappearing;


public:
   static void init(ResourcesPool & pool);
   static Square * create(double difficulty, unsigned width, unsigned height);

   Bomb();

   Square * clone() const override;
};






