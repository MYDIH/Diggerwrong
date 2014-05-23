#pragma once

#include "EventHandler.hh"
#include "Animation.hh"
#include "MenuView.hh"
#include "ConfigView.hh"

class GuiController : public EventHandler
{
public:
  GuiController();
  
  void draw(sf::RenderTarget & r, float now) override;
  int tick(sf::RenderWindow & w, float now) override;
  int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now) override;

private:
  MenuView vM;
  ConfigView vC;
  sf::Vector2f animOffsetMenu;
  sf::Vector2f animOffsetConfig;
  AnimatedValue slideAnim;
};
