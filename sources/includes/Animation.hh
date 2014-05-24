#pragma once

#include "resources.hh"
#include "utils.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <cmath>


float LINEAR(float);

template<unsigned LINE>
// LINE doit être dans ]0;+inf[ , quand LINE tend vers 0, la fonction tend vers f(x)=x (linéaire)
float EASE_IN_OUT(const float x)
{
   if (x == 0 or x == 1) return x;

   else                  return ( atan((x-0.5) * LINE)
				  / (-2 * atan(-0.5*LINE))
				  + 0.5 );
}



class AnimationResource : public Resource
{
private:
   static sf::Sprite Empty;
   sf::Color replacedColor;
   sf::Color withColor;
   sf::Image Image;
   sf::Image Image2;
   std::vector<sf::Drawable *> Frames;
   std::string Dir;
   std::string File;
   float Fps;
   bool Loop;
   bool isColorReplace;

   void load_image(sf::Image & image, const std::string & file, unsigned frames);

public:

   AnimationResource(const std::string & dir, const std::string & file);
   //AnimationResource(unsigned frame_count, float fps, bool loop); // constructeur de test (triangle qui tourne)
   ~AnimationResource() override;

   sf::Drawable & frame(float elapsed_time, float stopping_since) const;
   float remaining_time(float elapsed_time, float stopping_since) const;

   void dealloc();

   void load(const std::string & basepath) override;
   void createErrorImg();
};


class AnimatedValue
{
private:
   float Start_at;
   float Stop_after;
   float Start_value;
   float End_value;
   float (*Function)(float);
//    bool m_loop;

public:
   AnimatedValue(float endValue = 1, float startValue = 0
		 ,float duration = 10, float (*function)(float) = LINEAR);//, bool loop = false);

   void start(float at);
   void stop(float at);

   bool running(float at) const;

   float remaining_time(float at) const;

   float value(float now) const;

   // accesseurs
   float start_value() const;
   float end_value()   const;

   void set_value(float value);
   void set_start_value(float startValue);
   void set_end_value(float endValue);
   void swap();
   void restart_at_end(float newend);

};

class Animation
{
private:
   float Start_at;
   float Stop_after;
   const AnimationResource * Resource;

public:
   Animation(const AnimationResource * r);
   Animation(const Animation&);

   void start(float at);
   void stop(float at);

   bool running(float at) const;

   float remaining_time(float at) const;

  void draw(sf::RenderTarget & drawer, float now, float rotation = 0, const sf::Color &alpha = sf::Color(255, 255, 255, 255), const sf::Vector2f &scale = sf::Vector2f(0, 0)) const;
};


