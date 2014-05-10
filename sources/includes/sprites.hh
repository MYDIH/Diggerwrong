#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <list>

class AnimationResource
{
private:
   std::list<sf::Image> Images;
   std::vector<sf::Drawable *> Frames;
   float Fps;
   bool Loop;

public:
   AnimationResource(unsigned frame_count, float fps, bool loop); // constructeur de test (triangle qui tourne)
   ~AnimationResource();

   const sf::Drawable & frame(float elapsed_time, float stopping_since) const;
   float remaining_time(float elapsed_time, float stopping_since) const;
};

class Animation
{
private:
   const AnimationResource * Resource;

   float Start_at;
   float Stop_after;

public:
   Animation(const AnimationResource * r);

   void start(float at);
   void stop(float at);

   bool running(float at) const;

   float remaining_time(float at) const;

   void draw(sf::RenderTarget & drawer, float now) const;
};
