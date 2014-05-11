#pragma once

#include "Animation.hh"

#include <SFML/Graphics.hpp>

class SquareView
{
public:
   virtual ~SquareView();

   virtual void draw(sf::RenderTarget & drawer, float now)       const = 0;
   virtual void draw_above(sf::RenderTarget & drawer, float now) const = 0;

   virtual void tick(float now);

   virtual void appear(float at)    = 0;
   virtual void disappear(float at) = 0;
};

class AnimatedSquareView : public SquareView
{
protected:
   Animation Appearing;
   Animation Appearing_above;

   Animation Appeared;
   Animation Appeared_above;

   Animation Disappearing;
   Animation Disappearing_above;

public:
   AnimatedSquareView(const AnimationResource * appearing
		      ,const AnimationResource * appearing_above

		      ,const AnimationResource * appeared
		      ,const AnimationResource * appeared_above

		      ,const AnimationResource * disappearing
		      ,const AnimationResource * disappearing_above);

   AnimatedSquareView(const AnimatedSquareView &);

   void appear(float at)    override;
   void disappear(float at) override;

   void draw(sf::RenderTarget & drawer, float now)       const override;
   void draw_above(sf::RenderTarget & drawer, float now) const override;
};
