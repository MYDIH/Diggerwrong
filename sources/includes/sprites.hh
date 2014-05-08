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
   float remaning_time(float elapsed_time, float stopping_since) const;
};

class Animation
{
private:
   const AnimationResource * Resource;
public:
   Animation();

   void start();
   void stop();

   bool tick(float now);
   /* false si dernière frame atteinte ;
      pour afficher exactement le bon nombre 
      de frames, appeler draw() après chaque
      tick() (y compris le premier retournant false)

      exemple:
      | while ( s.tick(t) ) s.draw(d);
      | s.draw(d);
   */


   void draw(sf::RenderTarget & drawer);
};

class SquareSprite
{
   enum state
   {
      APPEAR
      ,NORMAL
      ,DISAPPEAR
   };

private:
/*
   AnimatedSprite Appear;
   AnimatedSprite Appear_above;

   AnimatedSprite Normal;
   AnimatedSprite Normal_above;

   AnimatedSprite Disappear;
   AnimatedSprite Disappear_above;
*/
   state State;

public:
   SquareSprite();

   void appear();
   void disappear();

   bool tick(float now);
   void draw(sf::RenderTarget & drawer);
};
