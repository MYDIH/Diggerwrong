#include "SquareView.hh"

#include <SFML/Graphics.hpp>

#include <iostream>

SquareView::~SquareView()
{}

void SquareView::tick(float now)
{
//   std::cout << "-- TICK\n";
}


AnimatedSquareView::AnimatedSquareView(const AnimationResource * appearing
				       ,const AnimationResource * appearing_above

				       ,const AnimationResource * appeared
				       ,const AnimationResource * appeared_above

				       ,const AnimationResource * disappearing
				       ,const AnimationResource * disappearing_above)

   :Appearing(appearing)
   ,Appearing_above(appearing_above)

   ,Appeared(appeared)
   ,Appeared_above(appeared_above)

   ,Disappearing(disappearing)
   ,Disappearing_above(disappearing_above)
{}

AnimatedSquareView::AnimatedSquareView(const AnimatedSquareView & o)
   :Appearing(o.Appearing)
   ,Appearing_above(o.Appearing_above)

   ,Appeared(o.Appeared)
   ,Appeared_above(o.Appeared_above)

   ,Disappearing(o.Disappearing)
   ,Disappearing_above(o.Disappearing_above)
{}
   
void AnimatedSquareView::appear(float at)
{
   Appearing.start( at );
   Appearing_above.start( at );

   Appeared.start( at + Appearing.remaining_time(at) );
   Appeared_above.start( at + Appearing_above.remaining_time(at) );
}
void AnimatedSquareView::disappear(float at)
{
   Appeared.stop( at );
   Appeared_above.stop( at );

   Disappearing.start( at + Appeared.remaining_time(at) );
   Disappearing_above.start( at + Appeared_above.remaining_time(at) );
}


void AnimatedSquareView::draw(sf::RenderTarget & drawer, float now) const
{
   if (Appearing.running(now))
   {
      std::cout << "";
      Appearing.draw(drawer, now);
   }

   else if (Appeared.running(now))
      Appeared.draw(drawer, now);

   else if (Disappearing.running(now))
      Disappearing.draw(drawer, now);
}
void AnimatedSquareView::draw_above(sf::RenderTarget & drawer, float now) const
{
   if (Appearing_above.running(now))
      Appearing_above.draw(drawer, now);

   else if (Appeared_above.running(now))
      Appeared_above.draw(drawer, now);

   else if (Disappearing_above.running(now))
      Disappearing_above.draw(drawer, now);
}



