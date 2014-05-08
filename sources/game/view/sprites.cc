#include "sprites.hh"


sf::Sprite AnimationResource::frame(float elapsed_time, float stopping_since = -1) const
{
   const unsigned size = Frames.size();

   if (Loop)
   {
      if (stopping_since >= 0)
      {
	 const float frame_f = (stopping_since * Fps);
	 const unsigned integer_part = frame_f;
	 const float delta = frame_f - integer_part;

	 const unsigned stopped_at_frame = integer_part % size;
	 const unsigned frame = ((elapsed_time - stopping_since) * Fps + delta) + stopped_at_frame;

	 if (frame >= size-1)
	    return Frames[ size-1 ];
	 else
	    return Frames[ frame ];

      }
      else
      {
	 return Frames[ (unsigned)(elapsed_time * Fps) % size ];
      }
   }
   else
   {
      const unsigned frame = elapsed_time * Fps;

      if (frame >= size-1)
	 return Frames[ size-1 ];
      else
	 return Frames[ frame ];
   }
}


#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )
float AnimationResource::remaining_time(float elapsed_time, float stopping_since = -1) const
{
   const unsigned size = Frames.size();

   if (Loop)
   {
      if (stopping_since >= 0)
      {
	 const float frame_f = (stopping_since * Fps);
	 const unsigned integer_part = frame_f;
	 const float delta = frame_f - integer_part;

	 const unsigned stopped_at_frame = integer_part % size;

	 return MAX(0, (size - stopped_at_frame - delta) / Fps - (elapsed_time - stopping_since));
      }
      else 
	 return -1;
   }
   else
      return MAX(0, (size / Fps) - elapsed_time);
}

Animation::Animation()
   :Resource(nullptr)
   ,Start_at(-1)
   ,Stop_at(-1)
   ,Elapsed_time(0)
{}

void Animation::tick(float now)
{
   if (Start_at >= 0 and now >= Start_at)
      Elapsed_time = now - Start_at;
}

void Animation::start(float at)
{ Start_at = at; }
void Animation::stop(float at)
{ Stop_at = at; }

float Animation::remaining_time() const
{
   if (Resource != nullptr)
      return Resource -> remaining_time(Elapsed_time, Stop_at);
   else
      return 0;
}

void Animation::draw(sf::RenderTarget & drawer) const
{
   if (Resource != nullptr)
      drawer.Draw( Resource -> frame(Elapsed_time, Stop_at) );
}


SquareAnimation::SquareAnimation()
   :Appear_at(-1)
   ,Disappear_at(-1)
   ,State(DISAPPEARED)
{}

void SquareAnimation::appear(float at)
{
   Appearing.start( at );
   Appearing_above.start( at );

   Normal.start( at + Appearing.remaining_time() );
   Normal_above.start( at + Appearing_above.remaining_time() );

   Appear_at = at;
}
void SquareAnimation::disappear(float at)
{
   Normal.stop( at );
   Normal_above.stop( at );

   Disappearing.start( at + Normal.remaining_time() );
   Disappearing_above.start( at + Normal_above.remaining_time() );

   Disappear_at = at;
}

void SquareAnimation::tick(float now)
{
   
}

void SquareAnimation::draw(sf::RenderTarget & drawer) const
{
   switch (State)
   {
      case APPEARING:    Appearing.draw(drawer);    break;
      case APPEARED:     Normal.draw(drawer);       break;
      case DISAPPEARING: Disappearing.draw(drawer); break;
      case DISAPPEARED:;
   }
}
void SquareAnimation::draw_above(sf::RenderTarget & drawer) const
{
   switch (State)
   {
      case APPEARING:    Appearing_above.draw(drawer);    break;
      case APPEARED:     Normal_above.draw(drawer);       break;
      case DISAPPEARING: Disappearing_above.draw(drawer); break;
      case DISAPPEARED:;
   }
}


