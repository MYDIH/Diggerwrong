#include "Animation.hh"

#include "consts.hh"
#include "utils.hh"

#include <iostream>
#include <cfloat>
#include <string>
#include <map>
#include <stdexcept>

#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )

const sf::Sprite AnimationResource::Empty;

AnimationResource::AnimationResource(const std::string & dir, const std::string & file)
   :Dir(dir + '/')
   ,File(file)
{}

// AnimationResource::AnimationResource(unsigned frame_count, float fps, bool loop)
//    :Fps(fps)
//    ,Loop(loop)
// {
//    sf::Shape model;
//    model.AddPoint(-7,-7);
//    model.AddPoint(+7,-7);
//    model.AddPoint(0,+10);
//    model.EnableFill(true);
//    model.EnableOutline(false);
//    model.SetColor(sf::Color(50,150,0));

//    if (loop)
//    {
//       const float rotation = 720 / (float)frame_count;

//       for (unsigned i = 0; i < frame_count; i++)
//       {
// 	 sf::Shape * shape = new sf::Shape(model);
// 	 Frames.push_back(shape);

// 	 shape -> Rotate(i * rotation);
// //	 std::cout << "frame rot=" << (unsigned)(2*i*rotation) << "\n";
//       }
//    }
//    else
//    {
//       const float alpha = 255 / (float)frame_count;

//       unsigned i;
//       for (i = 0; i < frame_count; i++)
//       {
// 	 sf::Shape * shape = new sf::Shape(model);
// 	 Frames.push_back(shape);

// 	 shape -> SetColor(sf::Color(50,150,0,i*alpha));
//       }
//    }
// }

AnimationResource::~AnimationResource()
{ dealloc(); }


const sf::Drawable & AnimationResource::frame(float elapsed_time, float stopping_since = FLT_MAX) const
{
   const unsigned size = Frames.size();

   if (size == 0)
      return Empty;

   if (Loop)
   {
      if (elapsed_time >= stopping_since)
      {
	 const float frame_f = (stopping_since * Fps);
	 const unsigned integer_part = frame_f;
	 const float delta = frame_f - integer_part;

	 const unsigned stopped_at_frame = integer_part % size;
	 const unsigned frame = ((elapsed_time - stopping_since) * Fps + delta) + stopped_at_frame;

	 if (frame >= size-1)
	 {
//	    std::cout << "ret. frame " << size-1 << "\n";
	    return *( Frames[ size-1 ] );
	 }
	 else
	 {
//	    std::cout << "ret. frame " << frame << "\n";
	    return *( Frames[ frame ] );
	 }

      }
      else
      {
//	 std::cout << "ret. frame " << (unsigned)(elapsed_time * Fps) % size << "\n";
	 return *( Frames[ (unsigned)(elapsed_time * Fps) % size ] );
      }
   }
   else
   {
      const unsigned frame = elapsed_time * Fps;

      if (frame >= size-1)
      {
//	 std::cout << "ret. frame " << size-1 << "\n";
	 return *( Frames[ size-1 ] );
      }
      else
      {
//	 std::cout << "ret. frame " << frame << "\n";
	 return *( Frames[ frame ] );
      }
   }
}


float AnimationResource::remaining_time(float elapsed_time, float stopping_since = FLT_MAX) const
{
   const unsigned size = Frames.size();

   if (size == 0)
      return 0;

   if (Loop)
   {
      if (elapsed_time >= stopping_since)
      {
	 const float frame_f = (stopping_since * Fps);
	 const unsigned integer_part = frame_f;
	 const float delta = frame_f - integer_part;

	 const unsigned stopped_at_frame = integer_part % size;

	 return MAX(0, (size - stopped_at_frame - delta) / Fps - (elapsed_time - stopping_since));
      }
      else
	 return FLT_MAX;
   }
   else
      return MAX(0, (size / Fps) - elapsed_time);
}

void AnimationResource::dealloc()
{
   for (sf::Drawable * frame : Frames)
      delete frame;

   Frames.clear();
}

void AnimationResource::load(const std::string & basepath)
{
   dealloc();

   std::map<std::string, std::string> descMap;

   if (not parseFile(descMap, basepath+Dir + File))
      throw basepath+Dir + File;
   
   try
   {
      if(not Image.LoadFromFile(basepath+Dir + descMap.at("image")))
	 throw basepath+Dir + descMap.at("image");
      
      Image.SetSmooth(false);

      const int frame_count = std::stoi(descMap.at("frames"));
      int spriteX = 1;
      const int frameWidth = Image.GetWidth() / frame_count;
      Fps = std::stof(descMap.at("fps"));
      Loop = (descMap.at("loop") == "true") ? true : false;


      for(int i = 1; i<=frame_count; i++)
      {
	 sf::IntRect clipRect(spriteX, 1, frameWidth*i - 1, Image.GetHeight());

	 Frames.push_back(new sf::Sprite(Image));
	 ((sf::Sprite*)Frames.back())->SetSubRect(clipRect);
	 ((sf::Sprite*)Frames.back())->SetCenter(frameWidth/2, Image.GetHeight()/2);

	 spriteX += frameWidth;
      }
   }
   catch(const std::out_of_range &oor)
   {
      throw basepath+Dir + File;
   }
   catch(const std::invalid_argument &ia)
   {
      throw basepath+Dir + File;
   }


}

// void AnimationResource::createErrorImg()
// {
//    Image.Create(50, 50, sf::Color(255, 0, 0));
//    Fps = 1;
//    Loop = false;

//     Frames.push_back(new sf::Sprite(Image));
//     ((sf::Sprite*)Frames.back())->SetCenter(Image.GetWidth()/2, Image.GetHeight()/2);
// }

//////////////////////////////////////////Animation/////////////////////////////////////////////////////

Animation::Animation(float start, float stop) :
    Start_at(start),
    Stop_after(stop)
{}

/////////////////////////////////////ValueAnimation//////////////////////////////////////////////////

ValueAnimation::ValueAnimation(float endValue, float startValue, float duration) : //, bool loop) :
   Animation(FLT_MAX, duration),
   m_startValue(startValue),
   m_endValue(endValue)
//    ,m_loop(loop)
{}

void ValueAnimation::start(float at)
{
   Start_at = MAX(0, at);
}

void ValueAnimation::stop(float at)
{
   if(at >= Start_at)
      Stop_after = at - Start_at;
//   m_loop = false;
}

bool ValueAnimation::running(float at) const
{
   if(at >= Start_at && at <= Start_at + Stop_after)
      return true;
   else
      return false;
}

float ValueAnimation::remaining_time(float at) const
{
   return MAX(0,Start_at + Stop_after - at);
}

float ValueAnimation::getValue(float now) const
{
//   if(m_loop && !running(now) && now > Start_at)
//        start(now);

   if(now < Start_at)
      return m_startValue;
   else if(now > Start_at + Stop_after)
      return m_endValue;
   else
      return m_startValue + ((m_endValue - m_startValue)/Stop_after*(now - Start_at));
}

//////////////////////////////////////SpriteAnimation///////////////////////////////////////////////////

SpriteAnimation::SpriteAnimation(const AnimationResource * r)
    :Animation(FLT_MAX, 0)
    ,Resource(r)
{}

SpriteAnimation::SpriteAnimation(const SpriteAnimation & o)
    :Animation(o.Start_at, o.Stop_after)
    ,Resource(o.Resource)
{}

void SpriteAnimation::start(float at)
{
   Start_at = MAX(0, at);

   Stop_after = (Resource == nullptr) ? 0 : Resource -> remaining_time(0);

}

void SpriteAnimation::stop(float at)
{
   if (at >= Start_at)
      Stop_after = at - Start_at;
}

bool SpriteAnimation::running(float at) const
{
   if (at >= Start_at and at < (Start_at+Stop_after + remaining_time(Start_at + Stop_after)))
      return true;
   else
      return false;
}

float SpriteAnimation::remaining_time(float at) const
{
   if (Resource != nullptr)
      return Resource -> remaining_time(MAX(0, at - Start_at), Stop_after);
   else
      return 0;
}

void SpriteAnimation::draw(sf::RenderTarget & drawer, float now) const
{
   if (Resource != nullptr)
      drawer.Draw( Resource -> frame(MAX(0, now - Start_at), Stop_after) );
}



