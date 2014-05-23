#pragma once

#include <SFML/Graphics.hpp>

#include <string>

class EventHandler
{
private:
  static const sf::Clock Clock;

  sf::View View;
  bool Need_refresh;


public:
  EventHandler();
  virtual ~EventHandler();

  int run(sf::RenderWindow & w);
  int call(sf::RenderWindow & w, sf::Event & t, float now);
  void need_refresh();
      
      
  /* Evenements */
  virtual void draw(sf::RenderTarget & r, float now);
  virtual int tick(sf::RenderWindow & w, float now);
  virtual int mouse_button_pressed(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now);
  virtual int mouse_button_released(sf::RenderWindow & w, sf::Event::MouseButtonEvent & e, float now);
  virtual int key_pressed(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now);
  virtual int key_released(sf::RenderWindow & w, sf::Event::KeyEvent & e, float now);
  virtual int mouse_moved(sf::RenderWindow & w, sf::Event::MouseMoveEvent & e, float now);
  virtual int resized(sf::RenderWindow & w, sf::Event::SizeEvent & e, float now);
  virtual int closed(sf::RenderWindow & w, float now);
};

