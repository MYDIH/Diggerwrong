#include "sprites.hh"


bool AnimationResource::frame(float elapsed_time, sf::Sprite & frame) const
{
   bool last_frame_reached;
   const unsigned frame_n = elapsed_time * Fps;

   frame = Frames[ Iterator(frame_n, Frames.size(), last_frame_reached, 0) ];
   
   return last_frame_reached;
}

bool AnimationResource::frame_stopping(float elapsed_time, float stopping_since, sf::Sprite & frame) const
{
   bool last_frame_reached;
   const unsigned frame_n = elapsed_time * Fps;
   const unsigned from_frame_n = stopping_since * Fps;

   frame = Frames[ Stopping_iterator(frame_n, Frames.size(), last_frame_reached, from_frame_n) ];
   
   return last_frame_reached;
}




bool Animation::tick(float now)
{
   /*

   if (Frames == nullptr or Frames -> size() == 0)
      return false;

   else
   {
      unsigned frame;

      if (not Started)
      {
	 Started = true;
	 First = now;

	 frame = 0;
      }
      else
	 frame = (unsigned) ((First - now) / (Duration / Frames->size()));

      
      switch(Iterator)
      {
	 case ONCE:
	    if (frame >= Frames->size() - 1)
	    {
	       Frame = Frames->size() - 1;
	       return false;
	    }
	    else
	    {
	       Frame = frame;
	       return true;
	    }

	 case LOOP:
	    Frame = frame % (Frames->size());
	    return true;

	 case BACK_AND_FORTH:
	    frame = frame % (Frames->size() * 2);

	    if (frame >= Frames->size())
	       Frame = 2*Frames->size() - frame - 1;
	    else
	       Frame = frame;

	    return true;
      }
   }

   return true; // pour le warning;

   */

   return true;
}

void Animation::draw(sf::RenderTarget & drawer)
{
/*
   if (Frames != nullptr and Frame < Frames->size())
      drawer.Draw( (*Frames)[Frame] );
*/
}


SquareSprite::SquareSprite()
   :State(NORMAL)
{}

void SquareSprite::appear()
{
}

void SquareSprite::disappear()
{
}

bool SquareSprite::tick(float now)
{
   return true;
}

void SquareSprite::draw(sf::RenderTarget & drawer)
{
}


