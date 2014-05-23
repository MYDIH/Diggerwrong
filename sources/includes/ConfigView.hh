#pragma once

#include <SFML/Graphics.hpp>

#include "Button.hh"
#include "Animation.hh"

class ConfigView
{
public:
  ConfigView();

  void setOffset(const sf::Vector2f &o);
  void show(float at);
  Button* isInButton(const sf::Vector2f &p);

  void draw(sf::RenderTarget &w, float now);

  Button cancel;

private:
  sf::Vector2f offset;
};
