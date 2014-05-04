#pragma once

#include <SFML/Graphics.hpp>

class SquareView
{
public:
   virtual void draw(sf::RenderTarget drawer);
   virtual void draw_above(sf::RenderTarget drawer);

   virtual void tick(float interval);

   virtual void appear();
   virtual void disappear();
}
