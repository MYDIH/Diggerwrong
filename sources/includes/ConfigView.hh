#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"

class ConfigView
{
public:
  ConfigView();

  void draw(sf::RenderTarget &w);
  
  void setOffset(const sf::Vector2f &o);

  Button play;
  Button options;
  Button quit;

private:
  sf::Vector2f offset;
};
