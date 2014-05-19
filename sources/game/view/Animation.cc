#include "Animation.hh"

#include "consts.hh"
#include "utils.hh"

#include <iostream>
#include <cfloat>
#include <string>
#include <map>
#include <stdexcept>

#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )

AnimationResource::AnimationResource(std::string dir) :
   Dir(dir)
{
   Frames.push_back(new sf::Sprite());
}

AnimationResource::AnimationResource(unsigned frame_count, float fps, bool loop)
   :Fps(fps)
   ,Loop(loop)
{
   sf::Shape model;
   model.AddPoint(-7,-7);
   model.AddPoint(+7,-7);
   model.AddPoint(0,+10);
   model.EnableFill(true);
   model.EnableOutline(false);
   model.SetColor(sf::Color(50,150,0));

   if (loop)
   {
      const float rotation = 720 / (float)frame_count;

      for (unsigned i = 0; i < frame_count; i++)
      {
	 sf::Shape * shape = new sf::Shape(model);
	 Frames.push_back(shape);

	 shape -> Rotate(i * rotation);
//	 std::cout << "frame rot=" << (unsigned)(2*i*rotation) << "\n";
      }
   }
   else
   {
      const float alpha = 255 / (float)frame_count;

      unsigned i;
      for (i = 0; i < frame_count; i++)
      {
	 sf::Shape * shape = new sf::Shape(model);
	 Frames.push_back(shape);

	 shape -> SetColor(sf::Color(50,150,0,i*alpha));
      }
   }
}

AnimationResource::~AnimationResource()
<<<<<<< HEAD
{ dealloc(); }
=======
{
   dealloc();
}
>>>>>>> 8cdafa96a618da366be8308e3ea605d892749688

const sf::Drawable & AnimationResource::frame(float elapsed_time, float stopping_since = FLT_MAX) const
{
   const unsigned size = Frames.size();

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
   std::map<std::string, std::string> descMap;

   dealloc();

//    exit(1);

   std::cout << basepath +'/'+ Dir +'/'+ DESC_FILENAME << std::endl;
   parseFile(descMap, basepath +'/'+ Dir +'/'+ DESC_FILENAME);
   if(descMap.size() >= 3)
   {
      try
      {
	 if(Image.LoadFromFile(basepath +'/'+ Dir +'/'+ SPRITE_FILENAME))
	 {
	    int spriteX = 1;
	    const int frameWidth = Image.GetWidth() / std::stoi(descMap.at("NbFrames"));
	    Fps = std::stof(descMap.at("Fps"));
	    Loop = (descMap.at("Loop") == "true") ? true : false;

	    std::cout << "parse.Loop: " << Loop << "\n";


	    for(int i = 1; i<=std::stoi(descMap.at("NbFrames")); i++)
	    {
	       sf::IntRect clipRect(spriteX, 1, frameWidth*i - 1, Image.GetHeight());

	       Frames.push_back(new sf::Sprite(Image));
	       ((sf::Sprite*)Frames.back())->SetSubRect(clipRect);
	       ((sf::Sprite*)Frames.back())->SetCenter(frameWidth/2, Image.GetHeight()/2);

	       spriteX += frameWidth;
	    }
	 }
	 else
	 {
	    std::cout << "img loading Error" << std::endl;
	    createErrorImg();
	 }
      }
      catch(const std::out_of_range &oor)
      {
	 createErrorImg();
	 std::cout << "exception error" << std::endl;
      }
   }
   else
   {
      createErrorImg();
      std::cout << "Parse Error" << descMap.size() << std::endl;
   }
}

void AnimationResource::createErrorImg()
{
   Image.Create(50, 50, sf::Color(255, 0, 0));
   Fps = 1;
   Loop = false;

    Frames.push_back(new sf::Sprite(Image));
    ((sf::Sprite*)Frames.back())->SetCenter(Image.GetWidth()/2, Image.GetHeight()/2);
}

//////////////////////////////////////////Animation/////////////////////////////////////////////////////

Animation::Animation(float start, float stop) :
    Start_at(start),
    Stop_after(stop)
{}

/////////////////////////////////////ValueAnimation//////////////////////////////////////////////////

ValueAnimation::ValueAnimation(float endValue, float startValue, float duration, bool loop) :
    Animation(FLT_MAX, 0),
    m_startValue(startValue),
    m_endValue(endValue),
    m_duration(duration),
    m_loop(loop)
{}

void ValueAnimation::start(float at)
{
    Start_at = MAX(0, at);
    if(m_duration > 0)
        Stop_after = Start_at + m_duration;
}

void ValueAnimation::stop(float at)
{
    if(at >= Start_at)
        Stop_after = at;
    m_loop = false;
}

bool ValueAnimation::running(float at) const
{
    if(at >= Start_at && at <= Stop_after)
        return true;
    return false;
}

float ValueAnimation::remaining_time(float at) const
{
    return Stop_after - Start_at;
}

float ValueAnimation::getValue(float now)
{
    if(m_loop && !running(now) && now > Start_at)
        start(now);

    if(running(now))
        return m_startValue + ((m_endValue - m_startValue)/m_duration*(now - Start_at));
    else if(now < Start_at)
        return m_startValue;
    else if(Stop_after < now)
        return m_endValue;

    return -1;
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

   if (Resource == &Normal::appearing)
      std::cout << "START: " << Start_at << "   STOPAFTER: " << Stop_after << "\n";
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



