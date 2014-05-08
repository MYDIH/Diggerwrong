#pragma once

#include <SFML/Graphics.hpp>


class AnimationResource
{
private:
   std::vector<sf::Sprite> Frames;
   float Fps;
   bool Loop;

public:
   sf::Sprite frame(float elapsed_time, float stopping_since) const;
   float remaining_time(float elapsed_time, float stopping_since) const;
};

class Animation
{
private:
   const AnimationResource * Resource;

   float Start_at;
   float Stop_at;

   float Elapsed_time;

public:
   Animation();

   void start(float at);
   void stop(float at);

   void tick(float now);

   float remaining_time() const;

   void draw(sf::RenderTarget & drawer) const;
};

class SquareAnimation
{
   enum state
   {
      APPEARING
      ,APPEARED
      ,DISAPPEARING
      ,DISAPPEARED
   };

private:
   Animation Appearing;
   Animation Appearing_above;

   Animation Normal;
   Animation Normal_above;

   Animation Disappearing;
   Animation Disappearing_above;


   float Appear_at;
   float Disappear_at;

   state State;
public:
   SquareAnimation();

   void appear(float at);
   void disappear(float at);

   void tick(float now);

   void draw(sf::RenderTarget & drawer) const;
   void draw_above(sf::RenderTarget & drawer) const;
};
