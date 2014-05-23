#pragma once

#include "Board.hh"
#include "SquareView.hh"
#include "Animation.hh"
#include "resources.hh"

#include <queue>
#include <vector>
#include <tuple>

class BoardView : public Board::Observer
{
private:
   typedef Board::change bc;

   std::vector< std::vector< std::pair<SquareView*, SquareView*> > > Squares;
   Board * Observed;

   AnimatedValue DiggerX;
   AnimatedValue DiggerY;
   Animation Digger;
   Animation Explosion;
   Animation Dead;

   unsigned Target;
   unsigned Reached;
   unsigned Score;
   unsigned Bonus_score;
   unsigned Bonus_lifes;


   void delete_squares();
   void replace(unsigned x, unsigned y, Square * newone, float now);
   void draw_squares(sf::RenderTarget & drawer, float now, bool above) const;

public:
   static AnimationResource ExplosionResource;
   static AnimationResource DiggerResource;
   static AnimationResource DeadResource;

   static FontResource  Score_font;
   static FontResource  Score_value_font;

   static SoundResource Score_sound;
   static SoundResource Bonus_sound;
   static SoundResource Life_sound;


   BoardView();
   ~BoardView();

   bool care(const Board::change&) override;

   void observe(Board * b, float appear_at);
   void tick(float now);

   bool moving() const;
   bool finished() const;

   void draw(sf::RenderTarget & drawer, float now) const;
};

