#pragma once

#include "resources.hh"

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

class AnimationResource : public Resource
{
private:
   static const sf::Sprite Empty;
   sf::Image Image;
   sf::Image Image2;
   std::vector<sf::Drawable *> Frames;
   std::string Dir;
   std::string File;
   float Fps;
   bool Loop;

   void load_image(sf::Image & image, const std::string & file, unsigned frames);

public:
   AnimationResource(const std::string & dir, const std::string & file);
   //AnimationResource(unsigned frame_count, float fps, bool loop); // constructeur de test (triangle qui tourne)
   ~AnimationResource() override;

   const sf::Drawable & frame(float elapsed_time, float stopping_since) const;
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
   float m_startValue;
   float m_endValue;
//    bool m_loop;

public:
   AnimatedValue(float endValue = 1, float startValue = 0, float duration = 10);//, bool loop = false);

   void start(float at);
   void stop(float at);

   bool running(float at) const;

   float remaining_time(float at) const;

   float value(float now) const;

   // accesseurs
   float start_value() const;
   float end_value()   const;

   void set_value(float value);
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

   void draw(sf::RenderTarget & drawer, float now) const;
};


